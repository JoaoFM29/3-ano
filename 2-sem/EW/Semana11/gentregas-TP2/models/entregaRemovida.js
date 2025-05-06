var mongoose = require("mongoose")

var entregaSchema = new mongoose.Schema({
    //_id : String, // Sigla
    removeDate : Date,
    uc : String,
    idProj : String,
    designacaoProj : String,
    designacaoEq : String,
    idEq : String,
    ficheiro : String, // path da entrega do ficheiro
    obs : String,
    justificacao : String
}, { versionKey: false })

module.exports = mongoose.model('entregasRemovidas', entregaSchema)