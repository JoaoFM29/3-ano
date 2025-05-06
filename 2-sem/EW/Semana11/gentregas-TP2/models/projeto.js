var mongoose = require("mongoose")

var projetoSchema = new mongoose.Schema({
    _id : String, // Sigla
    creationDate : Date,
    limitDate : Date,
    anoLetivo : String,
    uc : String,
    designacao : String,
    resumo : String,
    enunciado : String //path do ficheiro
}, { versionKey: false })

module.exports = mongoose.model('projeto', projetoSchema)