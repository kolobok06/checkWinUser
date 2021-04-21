const express = require("express");
const app = express();
const port = 8080;
const filePath = "C:\\Users\\Yury\\WebstormProjects\\untitled2";
const bodyParser = require("body-parser");

const getUsers = require("./build/Release/checkq");

app.use(express.static(filePath + "/public"));
app.use(bodyParser.json());

app.post("/backend/handler", async (req, res, next) => {
    let name = req.body.name;
    let users = getUsers.check().split("&");
    users.pop();
    res.json({hasUser: users.includes(name)});
    next();
})

app.listen(port, () => {
    console.log("server listening at port: ", port);
})