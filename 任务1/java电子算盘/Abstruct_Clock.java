package µÁ◊”À„≈Ã;

import java.util.Calendar;

public class Abstruct_Clock extends Thread
{
	protected int second;
	protected int minute;
	protected int hour;
	protected Calendar calendar;

	public Abstruct_Clock()
	{
		
		calendar = Calendar.getInstance();
		second = calendar.get(Calendar.SECOND);
		minute = calendar.get(Calendar.MINUTE);
		hour = calendar.get(Calendar.HOUR);
		new Thread(this).start();
	}

	public void run()
	{
		while (true)
		{
			try
			{Thread.sleep(1000);}
			catch (InterruptedException e)
			{e.printStackTrace();}
			second++;
			if (second == 60)
			{
				second = 0;
				minute++;
				if (minute == 60)
				{
					minute = 0;
					hour++;
				}
			}
		}
	}

	public int getSecond()
	{return second;}

	public int getMinute()
	{return minute;}

	public int getHour()
	{return hour;}
}
