import java.util.*;

class Warehouse {
  private Map<String, Product> map =  new HashMap<String, Product>();
    private ReentrantLock l = new ReentrantLock();

  private class Product {
    Condition cond = l.newCondition;
    int quantity = 0;
  }

  private Product get(String item) {
    Product p = map.get(item);
    if (p != null) return p;
    p = new Product();
    map.put(item, p);
    return p;
  }

  public void supply(String item, int quantity) {
    l.lock();
    try{
        Product p = get(item);
        p.quantity += quantity;
        p.cond.signalAll();
    }finally{
        l.unlock();
    }
  }

  public void consume(Set<String> items) throws InterruptedException {
        l.lock();
        try{
            List<Product> lp = new ArrayList<>();
            for(String s: items){
                lp.add(get(s));
            }
            for(;;){ //ciclo infinito
                Product p = missing(lp);
                if(p==null)
                    break;
                p.cond.await();
            }
            //ou também o que está em comentário
            /*
            Product aux;
            while((aux = missing(lp)) != null)
               p.cond.await();

            for (Product p : lp)
               p.quantity--;
            */
        }finally{
            l.unlock();
        }
     }

  public Product missing(List<Product> lp){
      for (Product p : lp)
          if(p.quantity == 0)
             return p;
      return null;
   }
}