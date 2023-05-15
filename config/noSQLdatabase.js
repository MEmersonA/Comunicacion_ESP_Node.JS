const mongoose = require("mongoose")
const {Schema} = mongoose

const db_uri = "mongodb+srv://memersonxdd:987123258456Em*@tempdatabasenosql.mfdqtis.mongodb.net/?retryWrites=true&w=majority"

async function connect(){
    try{
        await mongoose.connect(db_uri)
    } catch(err){
        console.log(err)
    }
}

connect()

const tempSchema = new Schema({

    temp: String,
    hora: String

})

const TempR = mongoose.model('temperature_register_db', tempSchema)

module.exports = TempR
