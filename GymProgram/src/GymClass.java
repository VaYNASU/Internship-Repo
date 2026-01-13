
public class GymClass {
    
    protected String customerName;
    protected int dataFit;
    protected int dataBoot;
    

    public GymClass(String customerName)
    {
        this.customerName = customerName;
        this.dataFit = 10;
        this.dataBoot = 10;
        
    }

    public GymClass(String customerName, int dataFit, int dataBoot)
    {
        this.customerName = customerName;
        this.dataFit = dataFit;
        this.dataBoot = dataBoot;
    }
    
    /*
     
    * These are getter methods. Allows program to return the customer's name and returns the remaining amount of fit or boot classes they have left.

    */
    public String getName()
    {
        return customerName;
    }

    public int getFitData()
    {
        return dataFit;
    }

    public int getBootData(){
        return dataBoot;
    }

    
   // Everytime they attend the fit class, it decrements by 1.

    public int fitModifier()
    {
        if(dataFit > 0)
        {
            dataFit--;
        }else if(dataFit == 0)
        {
            System.out.println("[[[[[No more Fitness class]]]]]");
        }
        
        return dataFit;
        
    }


    //Everytime they attend the boot class, it decrements by 1.


    public int bootModifier()
    {
        if(dataBoot > 0)
        {
            dataBoot--;
        }else if(dataBoot == 0)
        {
            System.out.println("[[[[[No more Bootcamp class]]]]]");
        }
        
        return dataBoot;
        
        
    }



}
