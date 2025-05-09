import asyncio
import websockets
import json

async def on_connect(websocket):
    print(f"Cliente conectado:")
    try:
        async for message in websocket:
            data = json.loads(message)  # Desserializa a mensagem JSON
            print(f"Mensagem recebida: {data}")
            ts = float(data["TR"]) -  12
            rhs = 0.99
            # Envia uma resposta de volta para o cliente
            response = {"tipo": "mensagem recebida", "ts": 5, "rhs": rhs}
            await websocket.send(json.dumps(response))  # Serializa a resposta como JSON

    except websockets.ConnectionClosed:
        print(f"Cliente desconectado: ")

async def main():
    server = await websockets.serve(on_connect, "localhost", 12345)
    print("Servidor iniciado na porta 12345...")
    await server.wait_closed()

asyncio.run(main())
