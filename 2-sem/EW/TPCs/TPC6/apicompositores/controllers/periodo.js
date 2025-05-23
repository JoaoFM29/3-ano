var Periodo = require("../models/periodo")

module.exports.list = () => { 
    return Periodo    
        .find()
        .sort({nome : 1})
        .exec()
}

module.exports.findById = id => {
    return Periodo
        .findOne({_id : id})
        .exec()
}

module.exports.insert = periodo => {
    return Periodo.create(periodo);
}
module.exports.update = (id, periodo) => {
    return Periodo.updateOne({_id: id}, periodo);
}

module.exports.delete = id => {
    return Periodo.findByIdAndDelete({_id: id});
}
