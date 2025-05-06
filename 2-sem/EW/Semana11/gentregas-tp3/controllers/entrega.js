const mongoose = require('mongoose')
var Entrega = require("../models/entrega")

module.exports.list = () => {
    return Entrega
        .find()
        .sort({designacao : 1})
        .exec()
}

module.exports.findById = id => {
    return Entrega
        .findOne({_id : id})
        .exec()
}

module.exports.findByProject = projectId => {
    return Entrega
        .find({projectId : projectId})
        .sort({designacao : 1})
        .exec()
}

module.exports.countProjects = projectId => {
    return Entrega
        .countDocuments({projectId : projectId})
        .exec()
}

module.exports.findByUc = ucId => {
    return Entrega
        .find({uc : ucId})
        .sort({designacao : 1})
        .exec()
}

module.exports.findByEquipa = idEquipa => {
    return Entrega
        .find({idEquipa : idEquipa})
        .sort({designacao : 1})
        .exec()
}

module.exports.insert = eq => {
    if((Entrega.find({_id : eq._id}).exec()).length != 1){
        var newEntrega = new Entrega(eq)
        return newEntrega.save()
    }
}

module.exports.update = (id, eq) => {
    return Entrega
        .findByIdAndUpdate(id, eq, {new : true})
        .exec()
}

module.exports.remove = id => {
    return Entrega
        .findByIdAndDelete(id)
        .exec()
}