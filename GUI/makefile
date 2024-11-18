# Variabile per la directory sorgente
SRC_DIR=src

# Installazione delle dipendenze
install:
	pip install -r requirements.txt

# Formattazione del codice
format:
	black .
	isort .

# Controllo di conformità (PEP 8, bug, ecc.)
lint:
	flake8 $(SRC_DIR)
	pylint $(SRC_DIR)

# Controllo dei tipi
type-check:
	mypy $(SRC_DIR)

# Analisi della sicurezza
security:
	bandit -r $(SRC_DIR)

# Test e copertura
test:
	pytest --cov=$(SRC_DIR)

# Generazione report di copertura
coverage:
	coverage html
	@echo "Apri il file htmlcov/index.html per vedere il report"

# Pre-commit
pre-commit:
	pre-commit run --all-files

# Esegui tutto (workflow completo)
all: format lint type-check security test

.PHONY: install format lint type-check security test coverage pre-commit all
