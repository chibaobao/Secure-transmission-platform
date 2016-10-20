# 报文编解码模块


1. 报文编解码根据type来编解码不同数据类型
2. 可以编解码的结构体有 ID_MsgKey_Req(请求报文) ID_MsgKey_Res(应对报文)

主要函数功能
	- MsgEncode		报文编码
	- MsgDecode		报文解码
	- MsgMemFree	报文编解码时malloc的释放掉
