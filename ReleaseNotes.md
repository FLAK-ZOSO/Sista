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

## v`0.8.0`

- Added [more ANSI cursor commands](https://github.com/FLAK-ZOSO/Sista/blob/3f861a7e1f61609f4d8f9cf03aaaf3c056db1278/include/sista/cursor.hpp#L70-L89)

```c++
enum EraseScreen {
    FROM_CURSOR_TO_END = 0,
    FROM_CURSOR_TO_BEGINNING = 1,
    ENTIRE_SCREEN = 2,
    ERASE_SAVED_LINES = 3,
};
enum EraseLine {
    LINE_FROM_CURSOR_TO_END = 0,
    LINE_FROM_CURSOR_TO_BEGINNING = 1,
    ENTIRE_LINE = 2,
};
enum MoveCursor {
    UP = (int)'A',
    DOWN = (int)'B',
    RIGHT = (int)'C',
    LEFT = (int)'D',
    BEGINNING_OF_NEXT_LINE = (int)'E',
    BEGINNING_OF_PREVIOUS_LINE = (int)'F',
    HORIZONTAL_ABSOLUTE = (int)'G'
};
enum MoveCursorDEC {
    SAVE_CURSOR_POSITION = 7,
    RESTORE_CURSOR_POSITION = 8
};
enum MoveCursorSCO {
    SCO_SAVE_CURSOR_POSITION = (int)'s',
    SCO_RESTORE_CURSOR_POSITION = (int)'u'
};

// In Cursor struct
void eraseScreen(EraseScreen eraseScreen_) {
    std::cout << CSI << eraseScreen_ << "J";
}
void eraseLine(EraseLine eraseLine_, bool moveCursor=true) {
    std::cout << CSI << eraseLine_ << "K";
    if (moveCursor) {
        this->set(this->y, 0);
        std::cout << '\r';
    }
}

void move(MoveCursor moveCursor_, unsigned short int n=1) {
    std::cout << CSI << n << (char)moveCursor_;
}
void move(MoveCursorDEC moveCursorDEC_) {
    std::cout << ESC << ' ' << moveCursorDEC_;
}
void move(MoveCursorSCO moveCursorSCO_) {
    std::cout << ESC << ' ' << moveCursorSCO_;
}
```

- Added `ESC` constant to `ANSI-Settings.hpp`


## v`0.9.0`

- Added 256 color support

```c++
void setForegroundColor(unsigned short int color) {
    std::cout << CSI << "38;5;" << color << "m";
}
void setBackgroundColor(unsigned short int color) {
    std::cout << CSI << "48;5;" << color << "m";
}
```

- Added 24-biit RGB color support

```c++
void setForegroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
    std::cout << CSI << "38;2;" << red << ";" << green << ";" << blue << "m";
}
void setBackgroundColor(unsigned short int red, unsigned short int green, unsigned short int blue) {
    std::cout << CSI << "48;2;" << red << ";" << green << ";" << blue << "m";
}
```
