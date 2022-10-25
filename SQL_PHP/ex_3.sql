-- 1)
-- APPARTAMENTO(CodA, Superficie, Indirizzo, Città)								-- KEY CodA
-- CONTRATTO-AFFITTO(CodA, DataInizio, DataFine, NomePersona, RettaMensile)		-- KEY CodA, DataInizio

-- 1A) Find the names of people who have entered into more than two leases for the same apartment (at different times).
SELECT NomePersona
FROM CONTRATTO-AFFITTO
GROUP BY CodA,NomePersona
HAVING COUNT(*) > 2;

-- 1B) Find the code and address of apartments in Turin where the monthly tuition was always more than 500 euros and for which there were at most 5 contracts.
SELECT A.CodA,Indirizzo
FROM APPARTAMENTO A, CONTRATTO-AFFITTO CA
WHERE A.CodA = CA.CodA
	AND Citta = ’Turin’
	AND A.CodA NOT IN
		(SELECT CodA FROM CONTRATTO-AFFITTO WHERE RettaMensile <= 500)
GROUP BY A.CodA, Indirizzo
HAVING COUNT(*) <= 5;
------------------------------------------------------------------
SELECT A.CodA,Indirizzo
FROM APPARTAMENTO A, CONTRATTO-AFFITTO CA
WHERE A.CodA = CA.CodA
	AND Citta = ’Turin’
GROUP BY A.CodA, Indirizzo
HAVING COUNT(*) <= 5
	AND MIN(RettaMensile) > 500;

-- 1C) Find the code and address of the apartments in Turin for which there are at most 5 contracts (a number varying between 0 and 5).
SELECT CodA,Indirizzo
FROM APPARTAMENTO
WHERE Citta = ’Turin’
	AND CodA NOT IN
		(SELECT CodA
		FROM CONTRATTO-AFFITTO
		GROUP BY CodA
		HAVING COUNT(*) > 5);


-- 2)
-- GARA(CodG, Luogo, Data, Disciplina)											-- KEY CodG
-- ATLETA(CodA, Nome, Nazione, DataNascita)										-- KEY CodA
-- PARTECIPAZIONE(CodG, CodA,PosizioneArrivo, Tempo)							-- KEY CodG, CodA

-- 2A) Find the name and date of birth of Italian athletes who did not participate in any downhill races.
SELECT Nome,DataNascita
FROM ATLETA
WHERE Nazione = ’Italy’
AND CodA NOT IN
	(SELECT CodA FROM PARTECIPAZIONE P,GARA G
	WHERE P.CodG=G.CodG
	AND G.Disciplina = ’downhill races’);

-- 2B) Find nations for which at least 5 athletes born before 1980 compete, each of whom has participated in at least 10 cross-country ski races.
SELECT Nazione
FROM ATLETA
WHERE DataNascita < ’1/1/1980’
	AND CodA IN
		(SELECT CodA
		FROM PARTECIPAZIONE P,GARA G
		WHERE P.CodG = G.CodG
			AND Disciplina = ’cross-country’
		GROUP BY CodA
		HAVING COUNT(*) >= 10)
GROUP BY Nazione
HAVING COUNT(*) >= 5;


-- 3) 
-- EDITORE(CodE, NomeEditore, Indirizzo, Città)									-- KEY CodE
-- PUBBLICAZIONE(CodP, Titolo, NomeAutore, CodE)								-- KEY CodP
-- LIBRERIA(CodL, NomeLibreria, Indirizzo, Città)								-- KEY CodL
-- VENDITA(CodP, CodL, Data,CopieVendute)										-- KEY CodP, CodL, Data

-- 3A) Find the name of the bookstores where no publications of Turin-based publishers were sold.
SELECT NomeLibreria
FROM LIBRERIA L
WHERE CodL NOT IN
	(SELECT CodL
	FROM VENDITA V, PUBBLICAZIONE P, EDITORE E
	WHERE V.CodP = P.CodP
		AND P.CodE = E.CodE
		AND Citta = ’Turin’);

-- 3B) Find the name of publishers for whom at least 10 publications sold more than 2,000 copies in 2002 in Rome bookstores.
SELECT NomeEditore
FROM EDITORE E, PUBBLICAZIONE P1
WHERE P1.CodE = E.CodE
	AND CodP IN
		(SELECT CodP
		FROM VENDITA V, LIBRERIA L
		WHERE V.CodL = L.CodL
			AND Data >= ’1/1/2002’ AND Data <= ’31/12/2002’
			AND L.Citta = ’Rome’
		GROUP BY CodP
		HAVING SUM(CopieVendute)>2000)
GROUP BY E.CodE, NomeEditore
HAVING COUNT(*) >= 10;


-- 4)
-- QUIZ(CodQuiz, Argomento, Punteggio)											-- KEY CodQuiz
-- STUDENTE(Matricola, Nome, Indirizzo, Città)									-- KEY Matricola
-- RISULTATO TEST(Matricola, CodQuiz,RispostaCorretta)							-- KEY Matricola, CodQuiz

-- 4A) Find the name of the students who did not answer any math quiz correctly.
SELECT Nome
FROM STUDENTE S
WHERE Matricola NOT IN
	(SELECT Matricola
	FROM RISULTATO_TEST R,QUIZ Q
	WHERE R.CodQuiz = Q.CodQuiz
		AND RispostaCorretta = ’yes’
		AND Argomento = ’math’);

-- 4B) Find the name of the students in Turin who scored the highest possible score on the math quizzes.
SELECT Nome
FROM STUDENTE S,RISULTATO_TEST R,QUIZ Q
WHERE S.Matricola = R.Matricola
	AND Q.CodQuiz = R.CodQuiz
	AND Citta = ’Turin’
	AND RispostaCorretta = ’yes’
	AND Argomento = ’math’
GROUP BY S.Matricola,Nome
HAVING SUM(Punteggio) =
	(SELECT SUM(Punteggio)
	FROM QUIZ
	WHERE Argomento = ’math’);


-- 5)
-- ALLOGGIO(CodA, Indirizzo,Città,Superficie,CostoAffittoMensile)				-- KEY CodA
-- CONTRATTO-AFFITTO(CodC, DataInizio,DataFine,NomePersona,CodA)				-- KEY CodC
-- Find the code, address, and city of housing units that have an area greater than the average housing area of the cities in which they are located.
SELECT CodA, Indirizzo, Citta
FROM ALLOGGIO A1
WHERE Superficie > 
	(SELECT AVG(Superficie)
	FROM ALLOGGIO A2
	WHERE A2.Citta = A1.Citta);


-- 6)
-- AEREI (Matr, Modello, NumPosti)												-- KEY Matr
-- ORARIO (Sigla, ParteDa, Destinaz, OraPart, OraArr)							-- KEY Sigla
-- VOLI (Sigla, Matr, Data, PostiPren)											-- KEY Sigla, Matr, Data
-- Find routes (departure city, arrival city) that have never been flown in a Boing-747 model aircraft.
SELECT ParteDa, Destinaz
FROM ORARIO O1
WHERE NOT EXISTS
	(SELECT *
	FROM ORARIO O2, VOLI V, AEREI A
	WHERE O2.Sigla = V.Sigla
		AND A.Matr = V.Matr
		AND A.Modello = ’Boing-747’
		AND O2.ParteDa = O1.ParteDa
		AND O2.Destinaz = O1.Destinaz);