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

module.exports.findByUc = idUc => {
    return Projeto
        .find({uc : idUc})
        .sort({designacao : 1})
        .exec()
}

module.exports.insert = proj => {
    if((Projeto.find({_id : proj._id}).exec()).length != 1){
        var newProjeto = new Projeto(proj)
        return newProjeto.save()
    }
}

module.exports.update = (id, proj) => {
    return Projeto
        .findByIdAndUpdate(id, proj, {new : true})
        .exec()
}

module.exports.remove = id => {
    Projeto
        .find({_id : id})
        .deleteOne()
        .exec()
}