# 簡介  
本編譯器可以解析基本的 C 語法結構，包括賦值語句、if 語句、while 語句以及 do while 語句，並生成對應的中間代碼。  
  
## 文件結構  
compiler.c：主要的編譯器邏輯，負責語法解析。  
compiler.h：編譯器的標頭檔，包含一些宏和函數原型。  
lexer.c：詞法分析器，負責將代碼轉換為 token。  