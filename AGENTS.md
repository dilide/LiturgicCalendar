# LiturgicCalendar 开发指南

本指南适用于整个仓库。公共接口在 `include/`，实现和命令行导出器在 `src/`，测试在 `test/liturgy_calendar_test.cpp`。修改计算规则时，优先通过 `Date` 或 `Calendar::getLiturgicDay` 验证实际调用者看到的结果。

## 构建和测试

在仓库根目录依次运行以下 Bash 命令。项目使用 C++11，SQLite 和 RapidJSON 已随仓库提供。当前云环境使用 CMake 3.31.6。

```bash
set -eu
repo=$(git rev-parse --show-toplevel)
cd "$repo"
cmake_bin=$(command -v cmake || echo /workspace/.liturgic-tools/cmake/data/bin/cmake)
"$cmake_bin" -S . -B build
"$cmake_bin" --build build --parallel 3
```

当前 CMake 配置只构建生成器。运行 Google Test 时，复用上一步的对象文件并排除含有生成器入口的 `main.cpp.o`。云环境已准备 Google Test 1.14.0，首次在其他环境运行时，下面的命令会获取相同版本。

```bash
gtest_root="$repo/build/googletest-1.14.0"
if [ ! -d "$gtest_root" ]; then
    git clone --depth 1 --branch v1.14.0 https://github.com/google/googletest.git "$gtest_root"
fi
test "$(git -C "$gtest_root" rev-parse HEAD)" = f8d7d77c06936315286eb55f8de22cd23c188571
gtest="$gtest_root/googletest"
objects="$repo/build/CMakeFiles/LiturgicCalendar.dir"
c++ -std=c++14 -pthread -Iinclude -I"$gtest/include" -I"$gtest" \
    test/liturgy_calendar_test.cpp "$gtest/src/gtest-all.cc" "$gtest/src/gtest_main.cc" \
    "$objects"/src/{Calendar,Date,LiturgicDay,LiturgicYear,MultiLang}.cpp.o \
    "$objects/include/sqlite/sqlite3.c.o" -ldl -o build/liturgy_calendar_test

run_dir=$(mktemp -d)
cp "$repo/lang.ini" "$run_dir/"
(cd "$run_dir" && "$repo/build/liturgy_calendar_test" --gtest_shuffle > tests.log 2>&1) || {
    tail -40 "$run_dir/tests.log"
    exit 1
}
tail -3 "$run_dir/tests.log"
```

## 验证导出

生成器和导出测试都会在当前目录重建文件，包括 `months/`、`liturgic.db` 和 SQL 文件。请从单独的运行目录启动，并将 `lang.ini` 放在该目录。下面的命令会生成所有语言的 ICS 文件，打印与仓库版本有差异的文件名。将需要发布的文件复制回仓库前，先核对变化的日期和庆典。

```bash
export_dir=$(mktemp -d)
cp "$repo/lang.ini" "$export_dir/"
(cd "$export_dir" && "$repo/build/LiturgicCalendar" > generator.log 2>&1)
for file in "$repo"/ics/*.ics; do
    diff -q "$file" "$export_dir/ics/${file##*/}" || test "$?" -eq 1
done
```

## 地区日期与礼仪规则

- `src/Date.cpp` 的年份表覆盖 1901–2100 年。春节与中秋分别以中国日期为基准，各自按语言记录日期差异。除夕从当地春节推算。核对中秋时取非闰八月十五。
- 日期查询与礼仪适用范围分别维护。当前只有韩语礼仪历显示秋夕。增加语言时，请同时核对当地历法和教会庆典规则。
- 为计算规则补测试时，使用独立核实的公历日期，覆盖节日前后和地区差异。多语言测试切换语言后初始化日历，结束时释放日历并恢复原语言，避免缓存影响其他用例。
