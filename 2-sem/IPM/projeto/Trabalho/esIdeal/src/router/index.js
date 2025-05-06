import { createRouter, createWebHistory } from 'vue-router'
import Home from '../views/Home.vue'
import SignInForm from '../views/SignInForm.vue'
import ServicePage from '../views/ServicePage.vue'
import History from '../views/History.vue'
import Station from '../views/Station.vue'
import NotFound from '../views/NotFound.vue'

const router = createRouter({
  history: createWebHistory(import.meta.env.BASE_URL),
  routes: [
    {
      path: '/',
      redirect: '/login'
    },
    {
      path: '/home/:stationID',
      name: 'home',
      component: Home
    },
    {
      path: '/login',
      name: 'login',
      component: SignInForm
    },
    {
      path: '/service/:serviceID',
      name: 'service',
      component: ServicePage,
      props:true
    },
    {
      path: '/history',
      name: 'history',
      component: History
    },
    {
      path: '/station',
      name: 'station',
      component: Station,
    },
    {
      path: '/:pathMatch(.*)', // Capturar qualquer coisa (caso onde as de cima falham todas)
      component: NotFound // Renderiza o componente NotFound para página não encontrada
    }
  ]
})

export default router

