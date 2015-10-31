fingerPrint
===========

Simple fingerPrint pattern matching, use Qt for UI


	时间		修改人		修改记录
	20151031	姚伟民		第一次编译运行报错：“QPixmap: It is not safe to use pixmaps outside the GUI thread”，也就是“对UI的操作只能放在UI主线程中，不能在子线程中处理。”，所以我做了更新，不创建原作者的线程，而是直接在主界面里面添加数据和操。