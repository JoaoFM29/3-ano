var mongoose = require("mongoose")

var entregaSchema = new mongoose.Schema({
    _id : String, // Sigla
    creationDate : Date,
    uc : String,
    projectId : String,
    designacao : String,
    idEquipa : String,
    desigEquipa : String,
    ficheiro : String, //path do ficheiro
    obs : String
}, { versionKey: false })

module.exports = mongoose.model('entrega', entregaSchema)