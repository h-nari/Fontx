# Fontx
Arduino Library, load FONTX and get glyph, utf8 to shiftjis conversion

## 概要

Fontxは、FONTXフォーマットのフォントファイルを扱うためのクラスです。
フォントデータから特定の文字のビットマップを取得することができます。

Humblsefot_GFXを経由し、小型LCDやOLEDなど様々なディスプレイに日本語
描画機能を追加するのに使用されています。

使用されているライブラリの例

* [h-nari/Humblesoft_GFX](https://github.com/h-nari/Humblesoft_GFX "h-nari/Humblesoft_GFX: arduino library, inherit Adafruit_GFX, expand functions, Kanji Font drawing ...")
* [h-nari/Humblesoft_ILI9341](https://github.com/h-nari/Humblesoft_ILI9341 "h-nari/Humblesoft_ILI9341: add some functions to Adaruit_ILI9341")
* [h-nari/Humblesoft_SSD1306](https://github.com/h-nari/Humblesoft_SSD1306 "h-nari/Humblesoft_SSD1306: arduino library for SSD1306, inherit Adafruit_SSD1306 add Kanji drawing feature")
* [h-nari/Humblesoft_LedMat](https://github.com/h-nari/Humblesoft_LedMat "h-nari/Humblesoft_LedMat: arduino library for Humblesoft Led Matrix controller with esp8266")

## クラス構造

## Fontx クラス

Fontxクラスはインターフェースを定義するための抽象クラスで、
実際にはRomFontx , FsFontxクラスでフォントを使用します。

### RomFontx クラス

RomFontxは、フォントのデータをプログラム中に配置し、
ROMに書き込みます。プログラムのサイズが大きくなり、
書込に時間がかかるようになるという欠点はありますが、
簡単に使用できます。

このクラスでは、FontxファイルをC言語の形式に変換して使用します。
変換プログラムはperlで書かれていて <a href="https://github.com/h-nari/Fontx/blob/master/fontx/fontx2h.pl">
fontx/fontx2h.pl</a>に置いてあります。

変換したファイルを用意して有りますので
Arduinoのスケッチから```#include```するだけで使用できます。

| 変換済みのファイル|         説明                            |
|:-----------------:|:---------------------------------------:|
| fontx/ILGH16XB.h  | IPAゴシックを元とした16dotフォント、半角 |
| fontx/ILGZ16XB.h  | IPAゴシックを元とした16dotフォント、全角 |
| fontx/font6x8.h   | Adafruit_GFXのデフォルトフォントをFONTX化したもの |

プログラムの例を以下に示します。

インクルードされたfontxのデータを用いて
RomFontxクラスのコンストラクタでRomFontxを生成します。

Fontxのフォントは、通常全角用と半角用でファイルが別れているため
RomFontxのコンストラクタは最大3つまでのfontxのデータを
指定することができます。

プログラムの例を示します。

``` c
#include <Fontx.h>
#include <fontx/ILGH16XB.h>
#include <fontx/ILGZ16XB.h>

RomFontx fontx1(ILGH16XB,ILGZ16XB);

...
Humblesoft_ILI9341 tft;

void setup()
{
    ...
    tft.setFont(&fontx);
    ...
}
```

使い方の例は examplesの
[romfontx_example](https://github.com/h-nari/Fontx/blob/master/examples/romfontx_example/romfontx_example.ino "Fontx/romfontx_example.ino at master · h-nari/Fontx")
にもあります。

### FsFontx クラス

FsFontxは、フォントのデータを<a href="https://github.com/esp8266/Arduino/blob/master/doc/filesystem.rst">ROM上に作成されたFileSystem</a>から読み出して
使用します。プログラムのサイズが大きくならないので、
書込時間が長くならないというメリットがありますが、
フォントデータをFileSystemに書き込む必要があります。

使い方の例はexamplesの
[fsfontx_example](https://github.com/h-nari/Fontx/blob/master/examples/fsfontx_example/fsfontx_example.ino "Fontx/fsfontx_example.ino at master · h-nari/Fontx")
にあります。

## Fontx ファイルの入手方法

このライブラリに同梱しているIPAフォントから作成されたフォントは
下記サイトのものを使用させて頂きました。

* <a href="http://ayati.cocolog-nifty.com/blog/2012/08/ipalx322416-64a.html">IPAフォントを元としたLXで使える32/24/16ドットフォント: こばこのひみつ</a>

さまざまなFontxフォントがネット上で公開されています。

* [$FONTX.SYS用フォント集 [DOS] - Diary on wind](http://lsair.html.xdomain.jp/a/e/console-fonts-for-fontx.html "$FONTX.SYS用フォント集 [DOS] - Diary on wind")
* [8×8 ドット日本語フォント「美咲フォント」](http://www.geocities.jp/littlimi/misaki.htm "8×8 ドット日本語フォント「美咲フォント」")

## 参考情報

本ライブラリ作成にあたっては、下記サイトを
大変参考にさせて頂きました。

* [FONTXの使いかた(elm-chan.org/docs/dosv/fontx.html)](http://elm-chan.org/docs/dosv/fontx.html "FONTXの使いかた")
