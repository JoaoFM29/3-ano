const mongoose = require('mongoose')
var Projeto = require("../models/projeto")

module.exports.list = () => {
    return Projeto
        .find()
        .sort({designacao : 1})
        .exec()
}

module.exports.findById = id => {
    return Projeto
        .findOne({_id : id})
        .exec()
}

module.exports.findByUC = uc => {
    return Projeto
        .find({uc : uc})
        .sort({designacao : 1})
        .exec()
}

module.exports.insert = eq => {
    if((Projeto.find({_id : eq._id}).exec()).length != 1){
        var newProjeto = new Projeto(eq)
        return newProjeto.save()
    }
}

module.exports.update = (id, eq) => {
    return Projeto
        .findByIdAndUpdate(id, eq, {new : true})
        .exec()
}

module.exports.remove = id => {
    Projeto
        .find({_id : id})
        .deleteOne()
        .exec()
}