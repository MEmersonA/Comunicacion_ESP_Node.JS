const express = require("express")
const { response } = require("express")
const bodyParser = require("body-parser")
const connection = require("./database")

const KEY = "esp";

const server = express()

server.use(bodyParser.urlencoded({extended: false}))
server.use(bodyParser.json())
server.use('/', express.static("public"))
server.use(express.json())
server.use(express.static('static'))
server.use(express.urlencoded({extended: true}))
server.set("view engine", "ejs")


let datosA = []
let datos

let form = ({ binLed: "0000", mode: "2" })

function Index(req, res) {

    res.render("index")
    console.log("XD")

}

function Bin(req, res){

    const bin = req.body
    form = bin
    form.mode = 1
    if(!bin){
        return res.status(400).json({error: "No hay datos :p"})
    }

    console.log(form)

}

function Led(req, res){

    const led = req.body
    form = led
    form.mode = 0
    if(!led){
        return res.status(400).json({error: "No hay datos :p"})
    }

    console.log(form)

}

function Sensor(req, res) {
    
    if(req.query.key == KEY){
        console.log("ESP Enviando datos...")
        datos = {"temperatura": req.query.temperatura, "fecha": new Date().toLocaleTimeString()}
        datosA.push(datos)
        res.send({"Status": 200})
    }else{
        res.status(401)
        res.send({"Error": "llave invalida"})
    }

    console.log(datos)
    console.log()

    connection.query(`INSERT INTO temperature_register_table (temperature_register, register_localtime) VALUES ("${datos.temperatura}°C", "${datos.fecha}")`, function(err, result){

                        if(err) throw err

                    })

}

function Enviar(req, res){

    if(req.query.key == KEY){
        console.log("Enviando datos a la ESP...")
        console.log(form)

        res.status(200).json(form)
     
    }else{
        res.status(401)
        res.send({"Error": "llave invalida"})
    }

    console.log()
    console.log()
    console.log("-------------------------------------------------")
    console.log()
    console.log()

}

function DataBase(){

    console.log("Servidor online")
    connection.connect((err) => {

        if(err) throw err;
        console.log("Conección exitosa a la base de datos!! :D")

    })

}

function Mostrar(req, res ){

    console.log("AAA")

    connection.query("SELECT * FROM temperature_register_table", (err, results) => {

        if(err) throw err

        console.log(results)
        res.render("db", {results:results})

    })

}

server.get("/", Index)
server.post("/bin", Bin)
server.post("/led", Led)
server.get("/Sensor", Sensor)
server.get("/Enviar", Enviar)
server.post("/mostrar", Mostrar)

server.listen(80, DataBase);
