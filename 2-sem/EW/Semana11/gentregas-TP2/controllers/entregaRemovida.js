const mongoose = require('mongoose')
var EntregaRemovida = require("../models/entregaRemovida")

module.exports.list = () => {
    return EntregaRemovida
        .find()
        .sort({creationDate : 1})
        .exec()
}

module.exports.findById = id => {
    return EntregaRemovida
        .findOne({_id : id})
        .exec()
}

module.exports.findByUc = idUc => {
    return EntregaRemovida
        .find({uc : idUc})
        .sort({creationDate : 1})
        .exec()
}

module.exports.findByProjeto = idProjeto => {
    return EntregaRemovida
        .find({idProj : idProjeto})
        .sort({creationDate : 1})
        .exec()
}

module.exports.countByProjeto = idProjeto => {
    return EntregaRemovida
        .countDocuments({idProj : idProjeto})
        .exec()
}

module.exports.findByEquipa = idEquipa => {
    return EntregaRemovida
        .find({idEq : idEquipa})
        .sort({creationDate : 1})
        .exec()
}

module.exports.insert = ent => {
    if((EntregaRemovida.find({_id : ent._id}).exec()).length != 1){
        var newEntregaRemovida = new EntregaRemovida(ent)
        return newEntregaRemovida.save()
    }
}

module.exports.update = (id, ent) => {
    return EntregaRemovida
        .findByIdAndUpdate(id, ent, {new : true})
        .exec()
}

module.exports.remove = id => {
    EntregaRemovida
        .find({_id : id})
        .deleteOne()
        .exec()
}