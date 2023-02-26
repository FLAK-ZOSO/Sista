# Release Notes

Here you can find the release notes for each version of `Sista` since `v0.1.0`, with changelog since v`0.7.0`.

## v`0.1.0`

This is the first version of `Sista` and it is still in development.

## v`0.7.1`

- Added [condition](https://github.com/FLAK-ZOSO/Sista/blob/main/include/sista/ANSI-Settings.hpp#L57-L60) over the attribute reset function

```c++
void resetAttribute(Attribute attribute) {
    if (attribute == Attribute::BRIGHT) {
        std::cout << CSI << attribute + 21 << "m";
        return;
    }
    std::cout << CSI << attribute + 20 << "m";
}
```

I added the if statement to check if the attribute is `BRIGHT` or not, because the `BRIGHT` reset code is `+21` (from set code) and the rest are `+20`.
