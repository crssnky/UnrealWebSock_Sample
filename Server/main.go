package main

import (
	"log"
	"net/http"
	"time"

	"github.com/gorilla/websocket"
)

var upgrader = websocket.Upgrader{
	// CORS
	CheckOrigin: func(r *http.Request) bool { return true },
}

func main() {
	http.HandleFunc("/", index)
	http.HandleFunc("/ws", msgHandler)

	log.Printf("server open")

	if err := http.ListenAndServe(":8080", nil); err != nil {
		log.Fatal(err)
	}
}

func index(w http.ResponseWriter, r *http.Request) {
	log.Printf("index")

	w.Write([]byte("index"))
}

func msgHandler(w http.ResponseWriter, r *http.Request) {
	ws, err := upgrader.Upgrade(w, r, nil)
	if err != nil {
		log.Println("upgrade:", err)
		return
	}
	defer ws.Close()

	ticker := time.NewTicker(time.Second * 1)
	for {
		<-ticker.C
		go sendTxt(ws)
	}
}

func sendTxt(ws *websocket.Conn) {
	now := time.Now()
	nowTxt := now.Format("2006/01/02 15:04:05")
	if err := ws.WriteMessage(websocket.TextMessage, []byte(nowTxt)); err != nil {
		log.Println("sendTxt:", err)
		return
	}
}
