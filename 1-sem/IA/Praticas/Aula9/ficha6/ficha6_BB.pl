
%LICENCIATURA EM ENGENHARIA INFORMÁTICA
%MESTRADO integrado EM ENGENHARIA INFORMÁTICA

%Inteligência Artificial
%2023/24

%Draft Ficha 6


% Extensao do predicado filho: Filho,Pai -> {V,F}

filho( joao,jose ).
filho( jose,manuel ).
filho( carlos,jose ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pai: Pai,Filho -> {V,F}

pai( P,F ) :- filho( F,P ).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado avo: Avo,Neto -> {V,F}

avo(A,N) :- filho(P,A), filho(N,P).
neto(N,A) :-avo(A,N).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado bisavo: Bisavo,Bisneto -> {V,F}

bisavo(B,N) :- avo(A,N), filho(A,B).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente -> {V,F}

descendente(X,Y) :- filho(X,Y).
descendente(X,Y) :- filho(X,A), filho(A,Y).




%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado descendente: Descendente,Ascendente,Grau -> {V,F}
descendente(X,Y,1) :- filho(X,Y).
descendente(X,Y,G) :- filho(X,Z), descendente(Z,Y,G1), G is G1+1.



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Construir a extensão de um predicado capaz de determinar se o indivíduo X é bisavô de Y;
BiavoG(A,N) :- descendente(N,A,3).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
%Construir a extensão de um predicado capaz de determinar se o indivíduo X é trisavô de Y;
TriavoG(A,N) :- descendente(N,A,4).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
%Construir a extensão de um predicado capaz de determinar se o indivíduo X é tetraneto de Y.
