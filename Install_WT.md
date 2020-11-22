# windows
[Reference](https://redmine.webtoolkit.eu/projects/wt/wiki/Installing_Wt_on_MinGW)

### Add Mingw of qt to your System Path
1. Right click **This PC** choose **Properties** /**Advanced system settings** /**Environment Variables**. 
2. In user variables set **Path** to your QT mingw 
	>C:\Qt\Tools\mingw730_64\bin

### First Step: Boost
1.  Install [Boost](https://www.boost.org/) version 1.6 newer and compress to the path C:\
2. Open Powershell command

	```
	cd  C:\boost_1_67_0
	./bootstrap.bat gcc
	./bjam.exe toolset=gcc link=static threading=multi --layout=versioned --prefix=c:/Boost --without-context install
	cmake /path/to/source -G "MinGW Makefiles" -DBoost_ARCHITECTURE="-x32"
	```

### Second Step: WT
