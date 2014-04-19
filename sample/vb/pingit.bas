Attribute VB_Name = "Module1"
Public Sub Main()
    earlyBound
    'lateBound
End Sub

Private Sub earlyBound()
    Dim czu As New Cheezy.Utilities
    Dim buffer As String
    
    czu.Ping "http://ping.blo.gs/", "Rob Fahrni", "http://rob.fahrni.ws", buffer
    Debug.Print buffer
End Sub

Private Sub lateBound()
    Dim cz As Object
    Dim buffer As String
    
    Set cz = CreateObject("Cheezy.Utilities")
    cz.Ping "http://ping.blo.gs/", "Rob Fahrni", "http://rob.fahrni.ws", buffer
    Debug.Print buffer
    
End Sub
