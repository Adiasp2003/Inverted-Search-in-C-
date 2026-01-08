# Inverted Search Engine (C)

This project implements an **Inverted Search Engine** in C to enable efficient keyword-based searching across multiple text files. The system builds an inverted index that maps each unique word to the files in which it appears, along with its frequency.

The project focuses on **data structures, file handling, and problem-solving** using the C programming language.

---

## 📌 Features

- Reads and processes multiple text files
- Builds an inverted index using **linked lists**
- Supports fast keyword-based search
- Displays file names and occurrence count for searched words
- Efficient memory usage and modular design

---

## 🛠️ Technologies Used

- **Language:** C  
- **Concepts:** Data Structures, Linked Lists  
- **File Handling:** Standard file I/O  
- **Algorithmic Logic:** Indexing and searching  

---

## 🧠 How It Works

1. Input text files are read line by line.
2. Each word is tokenized and stored in an inverted index.
3. The index maintains:
   - Word
   - List of files containing the word
   - Frequency of occurrence per file
4. When a keyword is searched, the index is queried to retrieve matching files efficiently.

---

## 📂 Project Structure

