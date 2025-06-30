if not exist build mkdir build
c:\gbdk\bin\lcc.exe -Ivwf/include -c -o build/vwf.o vwf/src/vwf.c
c:\gbdk\bin\lcc.exe -Ivwf/include -c -o build/vwf_font.o vwf/src/vwf_font.c
c:\gbdk\bin\lcc.exe -Ivwf/include -c -o build/vwf_font_bold.o vwf/src/vwf_font_bold.c
c:\gbdk\bin\lcc.exe -Ivwf/include -c -o build/vwf_font_ru.o vwf/src/vwf_font_ru.c
c:\gbdk\bin\lcc.exe -Ivwf/include -c -o build/vwf_a.o vwf/src/sm83/vwf_a.s

c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\background_cat.o backgrounds\background_cat.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\background_dog.o backgrounds\background_dog.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\SelectMenu_tileset.o backgrounds\SelectMenu_tileset.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\cat.o sprites\cat.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\cat_animated_2.o sprites\cat_animated_2.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\cat_animated.o sprites\cat_animated.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\cat_animated_.o cat_animated_.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\jester_sprite.o sprites\jester_sprite.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\jester.o jester.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\keyboarddata.o keyboard\keyboarddata.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\keyboardmap.o keyboard\keyboardmap.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\cursor.o sprites\cursor.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o build\keyboard.o keyboard.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -Wf-bo1 -Wf-ba1 -DUSE_SFR_FOR_REG -c -o build\pet_status.o pet_status.c

c:\gbdk\bin\lcc -Wl-yt0x1A -Wl-yo4 -Wl-ya4 -Wa-l -Wl-m -Wl-j  -DUSE_SFR_FOR_REG -o build\game.gb ^
    build\main.o ^
    build\background_cat.o ^
    build\background_dog.o ^
    build\SelectMenu_tileset.o ^
    build\cat.o ^
    build\cat_animated.o ^
    build\cat_animated_2.o ^
    build\cat_animated_.o ^
    build\jester_sprite.o ^
    build\jester.o ^
    build\cursor.o ^
    build\keyboarddata.o ^
    build\keyboardmap.o ^
    build\keyboard.o ^
    build\pet_status.o ^
    build\vwf.o ^
    build\vwf_font.o ^
    build\vwf_font_bold.o ^
    build\vwf_font_ru.o ^
    build\vwf_a.o



