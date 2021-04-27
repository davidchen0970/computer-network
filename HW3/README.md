HW-簡易的網頁爬蟲程式
--
請寫一個簡易的網頁爬蟲程式
基本款：寫讀到的html寫成html檔。
進階款：將該html檔裏的連結，也下載成html檔。
說明：一個web server上有四個html檔。其中index.html有連結至1.html,2.html,3.html檔。
index.html的內容為：

<html>
<body>Hello, world ! 
<a href="1.html">link 1</a> 
<a href="2.html">link 2</a> 
<a href="3.html">link 3</a> 
</body>
</html>

基本款：執行完，會輸出一個html檔案。
進階款：執行完，會輸出4個html檔案。
提示：爬蟲程式先取得index.html，發現有3個連結後，分別將三個html下載。
執行結果會將4個html下載至client端。