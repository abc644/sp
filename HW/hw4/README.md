# 多線程銀行應用程式
## 描述  
  
此練習演示了使用和不使用互斥體來管理競爭條件的多執行緒操作之間的差異。該任務涉及實現一個簡單的銀行應用程序，其中多個執行緒執行存款和提款操作。  
  
## 要求  
記錄初始帳戶餘額。  
記錄每筆存款和提款金額，以及每筆交易後的餘額。  
每次交易後驗證等式「初始餘額+存款-提款=剩餘餘額」是否成立。如果等式不成立，請回報錯誤。  
## 文件  
race.c：沒有互斥體的實現。  
norace.c：用互斥體實現。