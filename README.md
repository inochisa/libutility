# libutility

This is utility library, something like STL with enhanced extension
--------
Now is public domain, maybe change license to LGPLv2 if needed.  
This project will split into two project `libutility` and `libutilitysstdc++`  
  
### libutilitysstdc++ (the std part of libutility, include the stardand C library)

will have many implement defined interfaces and some light-weight extensions. in fact, some library TS is hard to support(such as parallel TS(many function to merge into cpp17, but no compiler support. <_<), and concept TS(will support when compiler support cpp20)), I will try it.
  
### libutility (extensions for libutilitysstdc++ and some useful tools)
#### main development of the library  
  
string_builder support: sync string build class (not a string, without some access functions)  
generate langange parser: use a mark language(see railway diagrams) to analyze all language(or just analyze the setting file the library used.)  
soucre_location(as a library TS2 class, which needs compiler support heavily...)  
Compression support  
crypto support  
enhanced support for cstdlib, cctypes(such as is_num) and other original C library (not include i/o function, will optimize at sstdc++ for safe and extend resons, please search to get answer)  
posix interface support(I think it should be in the sstdc++?)  
and something I forget...  

