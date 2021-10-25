# 打BiliBili小电视 小游戏

* 树莓派4
* 0.96寸OLED（SSD1306 SPI）
* 鼠标

## 说明

* BB是对拍死的BPI的计数,对应最终的成绩
* RANK是难度 数值越低难度越高 每当打死10个BPI以后就会减一即难度高一级 默认初始化RANK等于15
* DIE是存在的BPI数量,一旦数量大于或者等于5就GameOver了..........
* 最后会把最终成绩打印在屏幕和终端上

## 编译使用
进入文件夹
````
make
./game
````