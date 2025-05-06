%LICENCIATURA EM ENGENHARIA INFORMATICA
%MESTRADO integrado EM ENGENHARIA INFORMATICA

%Inteligencia Artificial
%2023/24

%Draft Ficha 7


% Parte I
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Operacoes aritmeticas

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

%--------------------------------- - - - - - - - - - -  -  -  -  -   -

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado soma: X,Y,Z,Soma -> {V,F}

soma( X,Y,Z,Soma ) :- Soma is X+Y+Z.



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado somaL: L ,Soma -> {V,F}
somaL([],0).
somaL([H|T], R) :- somaL(T, R1), R is R1+H.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado maior: X,Y,R -> {V,F}
maior(X,Y,X) :- X>Y.
maior(X,Y,Y) :- Y>X.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado maior: Lista, M, Resultado -> {V,}

maiorL([H], H, H).
maiorL([H|T], M, R) :- H =< M, maior(T, M, R).
maiorL([H|T], M, R) :- H > M, maior(T, H, R).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Quantidade de elementos de uma lista.
quantidade([],0).
quantidade([_|T], S) :- quantidade(T, G), S is G+1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Tamanho de uma Lista
tamL([_], 1) :- !.
tamL([_|L], T) :- tamL(L,X), T is X+1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Média aritmética de uma lista
mediaA([],0).
mediaA(L,M) :- soma(L,S), tamL(L,T),  M is S / T.


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% verificar se um numero é par

par(0).
par(X) :- N is X-2, N>=0, par(N).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado impar: N -> {V,F}
impar(1).
impar(X) :- N is X-2, N>=1, impar(N).

% Parte II--------------------------------------------------------- - - - - -



%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado pertence: Elemento,Lista -> {V,F}

pertence(X,[X|L]).
pertence(X,[Y|L]) :- X\= Y, pertence(X,L).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado comprimento: Lista,Comprimento -> {V,F}

comprimento([],0).
comprimento([_|T], S) :- comprimento(T, G), S is G+1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado quantos: Lista,Comprimento -> {V,F}

quantos([], 0).
quantos([H|T], R) :- pertence(H, T), quantos(T, R1).
quantos([H|T], R) :- not(pertence(H, T)), quantos(T, R1), R is R1 + 1.

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagar: Elemento,Lista,Resultado -> {V,F}

apagar(X,[X|R], R).
apagar(X,[Y|R], [Y|L]) :- X\= Y, remove(X,R,L).
          
%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado apagatudo: Elemento,Lista,Resultado -> {V,F}

apagatudo( X,[],[] ).
apagatudo( X,[X|R],L ) :- apagatudo(X,R,L).
apagatudo( X,[Y|R],[Y|L] ) :- X\= Y, apagatudo(X,R,L).


%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado adicionar: Elemento,Lista,Resultado -> {V,F}

adicionar(X,L,L) :- pertence(X,L).
adicionar(X,L,[X|L]):- not(pertence(X,L)).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado concatenar: Lista1,Lista2,Resultado -> {V,F}

concatenar([], L2, L2).
concatenar([X|R], L2, [X|L]):- concatenar(R,L2,l).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado inverter: Lista,Resultado -> {V,F}

inverter([],[]).
inverter([X|R], NL):- inverter(R,L), concatenar(L, [X], NL).

%--------------------------------- - - - - - - - - - -  -  -  -  -   -
% Extensao do predicado sublista: SubLista,Lista -> {V,F}
sublista(S,L):- concatenar(L1,L3,L), concatenar(S,L2, L3).