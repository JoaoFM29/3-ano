var Contrato = require("../models/contrato")

module.exports.list = () => { 
    return Contrato    
        .find()
        .exec()
}

module.exports.list2 = () => { 
    return Contrato    
        .distinct("entidade_comunicante")
        .sort()
        .exec()
}

module.exports.list3 = () => { 
    return Contrato    
        .distinct("tipoprocedimento")
        .sort()
        .exec()
}

module.exports.findById = id => {
    return Contrato
        .findOne({_id : id})
        .exec()
}

module.exports.insert = contrato => {
    return Contrato.create(contrato);
}

module.exports.update = (id, contrato) => {
    return Contrato.updateOne({_id: id}, contrato);
}

module.exports.delete = id => {
    return Contrato.findByIdAndDelete({_id : id});
}

module.exports.getEntidade = entidade => {
    return Contrato
        .find({NIPC_entidade_comunicante: entidade})
        .exec()
}

module.exports.getTipo = tipo => {
    return Contrato.find({ "tipoprocedimento": tipo});
}