GO-ClipImg
====
什么东西？What?
----
Qt和Golang混编开发的桌面应用，可用于批量提取图片的核心部分，并按照用户自定义的尺寸和位置以及边距生成新的图片。
图片的底色必须是白色或者其他纯色。

界面如下：
![github](https://github.com/george518/GO-ClipImg/blob/master/images/ui.png?raw=true "github")
<br/><br/>

【mac用户可以直接下载go-clipimg.dmg安装使用。】

有什么价值？
----
1、快速切割图片的核心部分，并自定义尺寸和边距形成新的图片   
2、常用于电商平台的图片批量处理。    
3、比其他golang的界面UI生成的应用要小很多。
4、可作为Qt与golang混编的参考案例。 

so ^_^ 求赐star !!!!!!!   

编译环境
----
mac pro
Qt Creator 4.41 （本项目使用此软件编辑代码）
golang 编译文件：PPGo_ClipImg（编译过程详见 https://github.com/george518/PPGo_ClipImg）
DMGhelp工具 用于添加图标

安装使用    
----
1、下载
```qt
git clone github.com/george518/GO_ClipImg 
```
2、编译qt
```shell
cd GO-ClipImg
qmake GO-ClipImg.pro -spec macx-clang CONFIG+=x86_64
make
```

3、拷贝golang 编译文件：PPGo_ClipImg到GO-ClipImg/Contents/MacOS/下。

4、获取需要依赖的QT包
```shell
GO-ClipImg otool -L ./GO-ClipImg.app/Contents/MacOS/GO-ClipImg 
```

5、将4中显示的文件拷贝到Contents/Frameworks中

6、打包编译Qt
```shell
/Applications/Qt/5.9.2/clang_64/bin/macdeployqt  ./GO-ClipImg.app 
```

7、在app包上右键单击进入显示简介，将logo.icns图标进去

8、使用DMGhelp工具，打包成dmg包（可以找我要工具）

9、生成的go-clipimg.dmg包点击显示简介，将logo.icns图标进去 

至此，生成的mac版的安装包 go-clipimg.dmg 就可以使用了……

联系我
----
qq:41352963    


