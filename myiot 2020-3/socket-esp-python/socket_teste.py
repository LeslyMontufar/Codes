import websocket

# Conecta no servidor WebSocket
ws = websocket.WebSocket()
ws.connect("ws://192.168.0.32")
print("Conectado no servidor WebSocket")

# Pede mensagem a ser transmitida 
str = input("Qual é a mensagem: ")
ws.send(str) #enviou

# Espera o servidor responder
print("O Servidor recebeu: " + ws.recv())

# Fecha a conexão  do WebSocket
ws.close()