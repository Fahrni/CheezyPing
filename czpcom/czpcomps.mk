
czpcomps.dll: dlldata.obj czpcom_p.obj czpcom_i.obj
	link /dll /out:czpcomps.dll /def:czpcomps.def /entry:DllMain dlldata.obj czpcom_p.obj czpcom_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del czpcomps.dll
	@del czpcomps.lib
	@del czpcomps.exp
	@del dlldata.obj
	@del czpcom_p.obj
	@del czpcom_i.obj
