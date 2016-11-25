Attribute VB_Name = "Module1"
Sub Main()
MsgBox "vor Load LibRef:" + Format(LibRef), vbOKOnly
'LibRef = LoadLibrary("C:\pro\pcs7lnk.ok\Pcs7easy.dll")
MsgBox "nach Load LibRef:" + Format(LibRef), vbOKOnly

Load EasyDemo
EasyDemo.Show
DoEvents
'MsgBox "Warte auf Ende", vbOKOnly
'Unload EasyDemo

End Sub
