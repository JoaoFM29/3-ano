<template>
    <div class="not-found-container">
      <div class="not-found-content">
        <h1>Oops! Página não encontrada</h1>
        <p>A página que está a tentar aceder não existe</p>
        <router-link to="/" class="back-link">Voltar para a página inicial</router-link>
      </div>
    </div>
  </template>
  
  <script>
  export default {
    name: 'NotFound'
  }
  </script>
  
  <style scoped>
  .not-found-container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 1000px;
    background-color: #F1F0F0; /* Cor de fundo */
  }
  
  .not-found-content {
    text-align: center;
    padding: 20px;
    background-color: #ffffff; /* Cor de fundo do conteúdo */
    border-radius: 8px;
    box-shadow: 0 2px 10px rgba(0, 0, 0, 0.1); /* Sombra */
  }
  
  h1 {
    font-family: 'Inter',sans-serif;
    font-size: 50px;
    color: #333333; /* Cor do título */
    margin-bottom: 20px;
  }
  
  p {
    font-family: 'Inter',sans-serif;
    font-size: 30px;
    color: #B5B5B5; /* Cor do texto */
    margin-bottom: 30px;
  }
  
  .back-link {
    font-family: 'Inter',sans-serif;
    display: inline-block;
    padding: 10px 20px;
    font-size: 20px;
    color: #ffffff;
    background-color: #1E56A0; 
    border-radius: 4px;
    text-decoration: none;
    transition: background-color 0.3s ease;
  }
  </style>
  