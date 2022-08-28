window.onload = function () {
  // const sock = new WebSocket("ws://localhost:8080/websocket");
  // const sock = new WebSocket("ws://localhost:8080/echo");
  const sock = new WebSocket("ws://localhost:8080/ws");
  sock.onopen = function () {
    console.log("sock.opened");
    updateTxt("opned");
  }

  sock.onmessage = function (e) {
    updateTxt(e.data)
  }
}

function updateTxt(msg) {
  const txt = document.getElementById("txt");
  txt.innerText = msg;
}
