const express = require('express')
const constroller = require("../controllers/user")
const router = express.Router()
const path = 'Leds'

router.get(`${path}`, constroller.getData)