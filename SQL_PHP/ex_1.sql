-- RIVISTA (CodR, NomeR, Editore)				-- KEY CodR
-- ARTICOLO (CodA, Titolo, Argomento, CodR)		-- KEY CodA

-- 1A) Find the code and name of magazines that have published at least one article on the topic 'motorcycling'
SELECT R.CodR, NomeR
FROM RIVISTA R, ARTICOLO A
WHERE R.CodR=A.CodR 
	AND Argomento=’motorcycling’;

-- 1B) Finding the code and name of magazines that have never published articles on the subject of 'motorcycling'
SELECT CodR, NomeR
FROM RIVISTA
WHERE CodR NOT IN
	(SELECT CodR
	FROM ARTICOLO
	WHERE Argomento=’motorcycling’);

-- 1C) Find the code and name of magazines that published only motorcycle articles
SELECT R.CodR, NomeR
FROM RIVISTA R, ARTICOLO A
WHERE R.CodR = A.CodR
	AND R.CodR NOT IN
		(SELECT CodR
		FROM ARTICOLO
		WHERE Argomento <> ’motorcycling’);

-- 1D) Find the code and name of magazines that publish motorcycle or car articles
SELECT R.CodR, NomeR
FROM RIVISTA R,ARTICOLO A
WHERE R.CodR=A.CodR
	AND (Argomento=’motorcycling’ OR Argomento=’car’);

-- 1E) Find the code and name of magazines that publish both motorcycle and car articles
SELECT R.CodR, NomeR
FROM RIVISTA R,ARTICOLO A
WHERE R.CodR=A.CodR
	AND Argomento=’motorcycling’
	AND R.CodR IN
		(SELECT CodR
		FROM ARTICOLO
		WHERE Argomento=’car’);

-- 1F) Find the code and name of magazines that have published at least 2 motorcycle articles
SELECT R.CodR, NomeR
FROM RIVISTA R,ARTICOLO A
WHERE R.CodR=A.CodR
	AND Argomento=’motorcycle’
GROUP BY R.CodR, NomeR
HAVING COUNT(*) >= 2;

-- 1G) Find the code and name of journals that have published only one motorcycle article (They may have written as many articles as they wish relative to other topics)
SELECT R.CodR, NomeR
FROM RIVISTA R ,ARTICOLO A
WHERE R.CodR=A.CodR
	AND Argomento=’motorcycle’
GROUP BY R.CodR, NomeR
HAVING COUNT(*) = 1;

---------------------------------------------------------------------------------------------

AEREO(Aid, ANome, Autonomia)		-- KEY Aid
CERTIFICATO(Did, Aid)				-- KEY Did, Aid
DIPENDENTE(Did, DNome, Stipendio)	-- KEY Did

-- 3A) Finding the codes and names of employees qualified to fly on an aircraft capable of covering distances greater than 5000 km (Autonomy > 5000)
SELECT D.Did, DNome
FROM DIPENDENTE D, CERTIFICATO C, AEREO A
WHERE D.Did = C.Did 
	AND C.Aid = A.Aid
	AND Autonomia > 5000;

-- 3B) Find codes and names of employees qualified to fly on at least two aircraft capable of covering distances greater than 5000 km (Autonomy>= 5000)
SELECT D.Did, DNome
FROM DIPENDENTE D, CERTIFICATO C, AEREO A
WHERE D.Did = C.Did 
	AND C.Aid = A.Aid
	AND Autonomia > 5000
GROUP BY D.Did, DNome
HAVING COUNT(*) >= 2;

-- 3C) Find the codes and names of flight-capable employees on at least two aircraft capable of covering distances greater than 5,000 km and who are flight-capable on some Boeings
-- a)
SELECT D.Did, DNome
FROM DIPENDENTE D, CERTIFICATO C, AEREO A
WHERE D.Did = C.Did AND C.Aid = A.Aid
	AND Autonomia > 5000
	AND Did IN
		(SELECT Did
		FROM CERTIFICATO C, AEREO A
		WHERE C.Aid = A.Aid
		AND ANome =’Boeing’)
GROUP BY D.Did, DNome
HAVING COUNT(*) >= 2;

-- b)
SELECT Did, DNome
FROM DIPENDENTE
WHERE Did IN
	(SELECT Did
	FROM CERTIFICATO C, AEREO A
	WHERE C.Aid = A.Aid
		AND Autonomia > 5000
	GROUP BY Did
	HAVING COUNT(*) >= 2)
	AND Did IN
		(SELECT Did
		FROM CERTIFICATO C, AEREO A
		WHERE C.Aid = A.Aid
			AND ANome =’Boeing’);