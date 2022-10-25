-- 1)
-- CORSO (CodCorso, NomeC, Anno, Semestre)								-- KEY CodCorso
-- ORARIO-LEZIONI (CodCorso, GiornoSettimana, OraInizio, OraFine, Aula)	-- KEY CodCorso, GiornoSettimana, OraInizio

-- 1A) Finding classrooms where first-year courses are never taught.
SELECT DISTINCT Aula
FROM ORARIO-LEZIONI
WHERE Aula NOT IN
	(SELECT Aula
	FROM ORARIO_LEZIONI OL, CORSO C
	WHERE OL.CodCorso = C.CodCorso
		AND C.Anno = 1);

-- 1B) Find course code, course name and total number of lecture hours per week for third-year courses for which the total number of lecture hours per week is more than 10 and classes are on more than three different days of the week.
SELECT C.CodCorso, C.NomeC, SUM(OraFine-OraInizio)
FROM CORSO C, ORARIO-LEZIONI OL
WHERE C.CodCorso=OL.CodCorso
	AND C.Anno = 3
GROUP BY C.Corso, C.NomeC
HAVING SUM(OraFine-OraInizio) > 10
	AND COUNT(DISTINCT GiornoSettimana) > 3;


-- 2)
-- ALLOGGIO (CodA, Indirizzo, Città, Superficie, CostoAffittoMensile)	-- KEY CodA
-- CONTRATTO-AFFITTO (CodC, DataInizio, DataFine, NomePersona, CodA)	-- KEY CodC

-- 2A) Find, for cities with at least 100 contracts, the city, the maximum monthly rental cost, the average monthly rental cost, the maximum contract duration, the average contract duration, and the 1 total number of contracts signed.
SELECT Citta, MAX(CostoAffittoMensile), AVG(CostoAffittoMensile),
MAX(DataFine-DataInizio), AVG(DataFine-DataInizio), COUNT(*)
FROM ALLOGGIO A, CONTRATTO-AFFITTO C
WHERE A.CodA=C.CodA
GROUP BY Citta
HAVING COUNT(*) >= 100;

-- 2B) Finding the name of people who have never rented housing with an area larger than 80 square meters.
SELECT DISTINCT NomePersona FROM CONTRATTO-AFFITTO
WHERE NomePersona NOT IN
	(SELECT NomePErsona
	FROM CONTRATTO-AFFITTO C, ALLOGGIO A
	WHERE C.CodA = A.CodA
		AND Superficie > 80);


-- 3) 
-- AEREI (Matr, Modello, NumPosti)										-- KEY Matr
-- ORARIO (Sigla, ParteDa, Destinaz, OraPart, OraArr)					-- KEY Sigla
-- VOLI (Sigla, Matr, Data, PostiPren)									-- KEY Sigla, Matr, Data

-- Find the abbreviation and departure time of flights departing from Milan to Naples on October 1, 1993, that still have free seats whose duration (difference between arrival time and departure time) is less than the average duration of flights from Milan to Naples.
SELECT Sigla, OraPart
FROM VOLI V, ORARIO O, AEREI A
WHERE V.Sigla = O.Sigla AND A.Matr = V.Matr
	AND O.ParteDa = 'Milan' AND O.Destinaz = 'Naples'
	AND V.Data = '1/10/93'
	AND A.NumPosti > V.PostiPren
	AND (O.OraArr-OraPart) < 
		(SELECT AVG(OraArr-OraPart)
		FROM VOLI V2, ORARIO O2
		WHERE V2.Sigla = O2.Sigla
			AND O2.ParteDa = 'Milan'
			AND O2.Destinaz = 'Naples');


-- 4) 
-- ORCHESTRA(CodO, NomeO, NomrDirettore, numElementi)					-- KEY CodO
-- CONCERTI(CodC, Data, CodO, CodS, PrezzoBiglietto)					-- KEY CodC
-- SALE(CodS, NomeS, Città, Capienza)									-- KEY CodS

-- Find the code and name of orchestras with more than 30 elements that have given concerts in both Turin and Milan and have never given concerts in Bologna.
SELECT O.CodO, O.NomeO
FROM ORCHESTRA O
WHERE O.NumElementi > 30
	AND O.CodO IN
		(SELECT C1.CodO 
		FROM CONCERTI C1, SALE S1
		WHERE C1.CodS = S1.CodS
			AND S1.Citta = 'Turin')
	AND O.CodO IN
		(SELECT C2.CodO 
		FROM CONCERTI C2, SALE S2
		WHERE C2.CodS = S2.CodS
			AND S2.Citta = 'Milan')
	AND O.CodO NOT IN
		(SELECT C3.CodO 
		FROM CONCERTI C3, SALE S3
		WHERE C3.CodS = S3.CodS
			AND S3.Citta = 'Bologna');


-- 5)
-- CLIENTE(Cod-Cli,nome)												-- KEY Cod-Cli
-- CONTO(Cod-Conto, saldo, agenzia, stato)								-- KEY Cod-Conto
-- CONTO-CLIENTE(Cod-Conto, Cod-Cli)									-- KEY Cod-Conto, Cod-Cli

-- Find all agencies that have at least one client who is the sole holder (without co-holders) of a single checking account (client to whom no other checking account is held).
SELECT DISTINCT C.Agenzia FROM Conto C, CONTO-CLIENTE CL
WHERE C.COD-CONTO = CL.COD-CONTO
	AND NOT EXISTS
		(SELECT *
		FROM CONTO-CLIENTE CL2
		WHERE CL2.DOC-CONTO = CL.COD-CONTO
		AND CL2.COD-CLI <> CL.COD-CLI)
	AND NOT EXISTS
		(SELECT * FROM CONTO-CLIENTE CL3
		WHERE CL3.COD-CLI = CL.COD-CLI
			AND CL3.COD-CONTO <> CL.COD-CONTO);

-- 6) 
-- CONTRIBUENTE(CodFiscale, Nome, Via, Città)							-- KEY CodFiscale
-- DICHIARAZIONE(CodDichiarazione, Tipo, Reddito)						-- KEY CodDichiarazione
-- PRESENTA(CodFiscale, CodDichiarazione, Data)							-- KEY CodFiscale, CodDichiarazione

-- Display code, name, and average of declared income from 1990 onward for taxpayers such that the maximum income they have declared since 1990 onward is higher than the average income calculated on all returns in the database.
SELECT C.CodFiscale, C.Nome, AVG(Reddito)
FROM CONTRIBUENTE C, DICHIARAZIONE D, PRESENTA P
WHERE C.CodFiscale = P.CodFiscale
	AND D.CodDichiarazione = P.CodDichiarazione
	AND P.Data > '1/1/1990'
GROUP BY C.CodFiscale, C.Nome
HAVING MAX(D.Reddito) > (SELECT AVG(Reddito) FROM DICHIARAZIONE);
---------------------------------------------------------------
SELECT C.CodFiscale, C.Nome, AVG(Reddito)
FROM CONTRIBUENTE C, DICHIARAZIONE D, PRESENTA P
WHERE C.CodFiscale = P.CodFiscale
	AND D.CodDichiarazione = P.CodDichiarazione
	AND P.Data > '1/1/1990'
	AND (SELECT MAX(Reddito) 
		FROM PRESENTA P1, DICHIARAZIONE D1
		WHERE P1.CodDichiarazione = D1.CodDichiarazione
			AND P1.CodFiscale = C.CodFiscale
			AND D1.Data > '1/1/1990') > (SELECT AVG(Reddito) FROM DICHIARAZIONE))
GROUP BY C.CodFiscale, C.Nome;

-- 7)
-- PERSONA(Nome, Sesso, Eta)											-- KEY Nome
-- GENITORE(Nome-Gen, Nome-Figlio)										-- KEY Nome-Gen, Nome-Figlio

-- Find the name of all persons under the age of 10 who are only children.
SELECT DISTINCT NOME FROM PERSONA P, GENITORE G
WHERE P.NOME = G.NOME-FIGLIO
	AND P.ETA < 10
	AND P.NOME NOT IN
		(SELECT G1.NOME-FIGLIO
		FROM GENITORE G1, GENITORE G2
		WHERE G1.NOME-GEN = G2.NOME-GEN
			AND G1.NOME-FIGLIO <> G2.NOME-FIGLIO);
