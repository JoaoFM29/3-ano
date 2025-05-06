def comprarFruta(fruta, numKgs):
 if fruta not in precosFruta:
    print("Lamento mas não temos %s" % (fruta))
 else:
    custo = precosFruta[fruta] * numKgs
    print("Serão %f euros, por favor" % (custo))