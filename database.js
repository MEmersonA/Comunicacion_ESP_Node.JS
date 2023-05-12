const mysql = require("mysql")

const connection = mysql.createConnection({

    host: 'localhost',
    database: 'temperature_database',
    user: 'root',
    password: '987123'

})

module.exports = connection