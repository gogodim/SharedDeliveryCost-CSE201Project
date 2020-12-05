# Windows
[Reference](https://redmine.webtoolkit.eu/projects/wt/wiki/Installing_Wt_on_MinGW)

### Add Mingw of qt to your System Path
1. Right click **This PC** choose **Properties** /**Advanced system settings** /**Environment Variables**. 
2. In user variables set **Path** to your QT mingw 
	>C:\Qt\Tools\mingw730_64\bin

### First Step: Boost
1.  Install [Boost](https://www.boost.org/) version 1.6 newer and compress it to path C:\
2. Open Powershell command
	```
	cd  C:\boost_1_67_0
	./bootstrap.bat gcc
	./bjam.exe toolset=gcc link=static threading=multi --layout=versioned --prefix=c:/Boost --without-context install
	```
3. Wait 30 minutes for building boost in C:/Boost
4. Test boost in your QT-creator by adding following lines in your .pro
	```
	INCLUDEPATH  +=  C:/Boost/include/boost-1_67
	LIBS  +=  -LC:/Boost/lib \
			-llibboost_locale-mgw73-mt-x64-1_67 \
			-llibboost_thread-mgw73-mt-x64-1_67 \
			-llibboost_program_options-mgw73-mt-x64-1_67 \
			-llibboost_filesystem-mgw73-mt-x64-1_67 \
			-llibboost_system-mgw73-mt-x64-1_67
	```
### Second Step: WT
1. In **Environment Variables** add new variable in **User variables for user**
	```
	Variable name: BOOST_ROOT
	Variable value: C:\Boost
	Variable name: BOOST_INCLUDEDIR
	Variable value: C:\Boost\include
	Variable name: BOOST_PREFIX
	Variable value: C:\Boost
	Variable name: BOOST_LIBRARYDIR
	Variable value: C:\Boost\lib
	```
2. Find **FontSupportDirectWrite.C** in C:\wt-4.4.0\src\Wt, comment following lines so it would make successfully
	```
	IDWriteLocalFontFileLoader *localFontLoader = NULL;
	...
	SafeRelease(localFontLoader);
	```
3.  Install [WT](https://www.webtoolkit.eu/wt/download) and compress it to path C:\ ,command it would take about an hour to make
	```
	cd  C:\wt-4.4.0
	cmake C:\wt-4.4.0 -G "MinGW Makefiles" -DBoost_ARCHITECTURE="-x64"
	mingw32-make
	```
4. Test WT in your QT-creator by adding following lines **in order** with in your .pro 
	```
	INCLUDEPATH  +=  C:/Boost/include/boost-1_67  \
					 C:/wt-4.4.0/src \
					 C:/wt-4.4.0
	LIBS  +=  -LC:/wt-4.4.0/src/http  -llibwthttp  \
			-LC:/wt-4.4.0/src  -llibwt  \
			-LC:/wt-4.4.0/src/Wt/Dbo  -llibwtdbo  \
			-LC:/wt-4.4.0/src/Wt/Dbo/backend  -llibwtdbosqlite3
	LIBS  +=  -lole32
	LIBS  +=  -LC:/Boost/lib \
			-llibboost_locale-mgw73-mt-x64-1_67 \
			-llibboost_thread-mgw73-mt-x64-1_67 \
			-llibboost_program_options-mgw73-mt-x64-1_67 \
			-llibboost_filesystem-mgw73-mt-x64-1_67 \
			-llibboost_system-mgw73-mt-x64-1_67
	
	LIBS  +=  -LC:/Qt/Tools/mingw730_64/i686-w64-mingw32/lib  \
			-llibws2_32  \
			-llibwsock32
	```
### After all of this, you can start to run WT in your QT-creator with **64 DEBUG**
