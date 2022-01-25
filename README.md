# /dev/twitter_fav
(Format:UTF-8)  
A module to make the /dev/twitter_fav

## 概要
**これはジョークソフトです。常用や他人と共有しているPCでは実行しないでください。**  
/dev/twitter_favを生やすための怪しいソフトです。  
対象ユーザの最新のfavoriteのidを返します。  
API Rate Limitに引っかかるのでそんなに頻繁に使えません。

## ビルド
### 依存関係

* build-essential
* kernel-header
* curl
* jq
* openssl

dev_twitter.cと同じディレクトリに"key"を作成します。  
https://developer.twitter.com からアプリを作成するか、既存のアプリのトークンを持ってきて以下のように記述します。  
TARGET_USERにはfavoriteの情報を取得する対象のユーザのスクリーンネームを入れます。

```
CONSUMER_KEY=xxxxxxxxxxxxxxxxxxxxxxxx
CONSUMER_SECRET=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
ACCESS_TOKEN=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
ACCESS_TOKEN_SECRET=xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx
TARGET_USER=HOGE_USER_SCREEN_NAME
```

### ビルド

```
$ make
$ sudo make load
$ head -n 1 /dev/twitter_fav
$ sudo make unload # 電源を切る前に行ってください
```

## usptomo-tweet

https://github.com/ryuichiueda/TomoTool

```
The MIT License

Copyright (C) 2013-2015 Ryuichi Ueda

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
```
