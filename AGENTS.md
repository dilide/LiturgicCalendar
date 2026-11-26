# LiturgicCalendar 开发指南

本指南适用于整个仓库。公共接口在 `include/`，实现和命令行导出器在 `src/`，测试在 `test/liturgy_calendar_test.cpp`。修改计算规则时，优先通过 `Date` 或 `Calendar::getLiturgicDay` 验证实际调用者看到的结果。

## 构建和测试

在仓库根目录运行 `make`（并行构建可用 `make -j3`）。默认构建生成器和测试程序，每次都通过 CTest 运行 Google Test；测试失败会使构建失败。测试在构建目录的 `test-output/` 中运行，完整日志位于 `Testing/Temporary/LastTest.log`。

需要 CMake 3.14 或以上版本及支持 C++14 的测试编译器。找不到已安装的 Google Test 时，CMake 会获取固定的 1.14.0 源码。云环境中若 CMake 未加入 PATH，可在首次配置时使用 `make CMAKE=/workspace/.liturgic-tools/cmake/data/bin/cmake`。

## 验证导出

生成器和导出测试都会在当前目录重建文件，包括 `months/`、`liturgic.db` 和 SQL 文件。请从单独的运行目录启动，并将 `lang.ini` 放在该目录。下面的命令会生成所有语言的 ICS 文件，打印与仓库版本有差异的文件名。将需要发布的文件复制回仓库前，先核对变化的日期和庆典。

```bash
set -eu
repo=$(git rev-parse --show-toplevel)
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
