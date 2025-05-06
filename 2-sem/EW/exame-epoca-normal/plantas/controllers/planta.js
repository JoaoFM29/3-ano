var Planta = require("../models/planta")

module.exports.list = () => { 
    return Planta    
        .find()
        .sort({Rua : 1})
        .exec()
}

module.exports.findById = id => {
    return Planta
        .findOne({_id : id})
        .exec()
}

module.exports.insert = planta => {
    return Planta.create(planta);
}

module.exports.update = (id, planta) => {
    return Planta.updateOne({_id: id}, planta);
}

module.exports.delete = id => {
    return Planta.findByIdAndDelete({_id : id});
}

module.exports.distinct1 = () => {
    return Planta.distinct("Freguesia")   ;
}

module.exports.distinct2 = () => {
    return Planta.distinct("Espécie")      ;
}

module.exports.getEspecie = especie => {
    return Planta.find({ Espécie: especie});
}

module.exports.getImplant = impl => {
    return Planta.find({ Implantação: impl});
}