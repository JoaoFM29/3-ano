const mongoose = require('mongoose')
var EntregaRemovida = require("../models/entregaRemovida")

module.exports.list = () => {
    return EntregaRemovida
        .find()
        .exec()
}

module.exports.findById = id => {
    return EntregaRemovida
        .findOne({_id : id})
        .exec()
}

module.exports.findByProject = projectId => {
    return EntregaRemovida
        .find({projectId : projectId})
        .exec()
}

module.exports.countProjects = projectId => {
    return EntregaRemovida
        .countDocuments({projectId : projectId})
        .exec()
}

module.exports.findByUc = ucId => {
    return EntregaRemovida
        .find({uc : ucId})
        .exec()
}

module.exports.findByEquipa = idEquipa => {
    return EntregaRemovida
        .find({idEquipa : idEquipa})
        .exec()
}

module.exports.insert = eq => {
    if((EntregaRemovida.find({_id : eq._id}).exec()).length != 1){
        var newEntregaRemovida = new EntregaRemovida(eq)
        return newEntregaRemovida.save()
    }
}

module.exports.update = (id, eq) => {
    return EntregaRemovida
        .findByIdAndUpdate(id, eq, {new : true})
        .exec()
}

module.exports.remove = id => {
    EntregaRemovida
        .find({_id : id})
        .deleteOne()
        .exec()
}