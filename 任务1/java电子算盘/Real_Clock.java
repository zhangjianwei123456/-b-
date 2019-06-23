package µÁ◊”À„≈Ã;

import java.awt.*;
import java.util.Calendar;
import javax.swing.*;

public class Real_Clock extends JPanel implements Runnable
{
	protected static final long serialVersionUID = 7948448358363802293L;
	protected final BasicStroke HOURS_POINT_WIDTH = new BasicStroke(5);
	protected final BasicStroke MINUETES_POINT_WIDTH = new BasicStroke(3);
	protected final BasicStroke SEC_POINT_WIDTH = new BasicStroke(2);
	protected ImageIcon background;
	protected int center_X;
	protected int center_Y;
	protected final static int sLen = 60;
	protected final static int mLen = 45;
	protected final static int hLen = 20;

	protected Abstruct_Clock abstruct_Clock;

	public Real_Clock()
	{
		abstruct_Clock = new Abstruct_Clock();
		setOpaque(false);
		background = new ImageIcon("src/images/clock.png");
		int iconWidth = background.getIconWidth();
		center_X = iconWidth / 2;
		int iconHeight = background.getIconHeight();
		center_Y = iconHeight / 2;
		setPreferredSize(new Dimension(532, 286));
		new Thread(this).start();
	}

	public void paint(Graphics g)
	{
		Graphics2D g2 = (Graphics2D) g.create();
		Composite composite = g2.getComposite();
		g2.setComposite(AlphaComposite.SrcOver.derive(0.6f));
		Calendar calendar = Calendar.getInstance();
		drawClock(g2, calendar);
		g2.setComposite(composite);
		g2.drawImage(background.getImage(), 0, 0, this);
		g2.dispose();
	}

	protected void drawClock(Graphics2D g2, Calendar calendar)
	{
		int sec = abstruct_Clock.getSecond();
		int minutes = abstruct_Clock.getMinute();
		int hours = abstruct_Clock.getHour();
		double secAngle = (60 - sec) * 6;
		int minutesAngle = (60 - minutes) * 6;
		int hoursAngle = (12 - hours) * 360 / 12 - (minutes / 2);
		int secX = (int) (sLen * Math.sin(Math.toRadians(secAngle)));
		int secY = (int) (sLen * Math.cos(Math.toRadians(secAngle)));
		int minutesX = (int) (mLen * Math.sin(Math.toRadians(minutesAngle)));
		int minutesY = (int) (mLen * Math.cos(Math.toRadians(minutesAngle)));
		int hoursX = (int) (hLen * Math.sin(Math.toRadians(hoursAngle)));
		int hoursY = (int) (hLen * Math.cos(Math.toRadians(hoursAngle)));
		g2.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g2.setColor(Color.BLACK);
		g2.setStroke(HOURS_POINT_WIDTH);
		g2.drawLine(center_X, center_Y, center_X - hoursX, center_Y - hoursY);
		g2.setStroke(MINUETES_POINT_WIDTH);
		g2.setColor(new Color(0x2F2F2F));
		g2.drawLine(center_X, center_Y, center_X - minutesX, center_Y - minutesY);
		g2.setColor(Color.RED);
		g2.setStroke(SEC_POINT_WIDTH);
		g2.drawLine(center_X, center_Y, center_X - secX, center_Y - secY);
		g2.fillOval(center_X - 5, center_Y - 5, 10, 10);
	}

	public void run()
	{
		try
		{
			while (true)
			{
				if (getRootPane() != null)
				{
					JFrame main = (JFrame) getRootPane().getParent();
					if (main != null && main.isVisible())
					{
						EventQueue.invokeLater(new Runnable()
						{
							public void run()
							{
								Real_Clock.this.repaint();
							}
						});
					}
				}
				Thread.sleep(100);
			}
		} catch (InterruptedException e)
		{
			e.printStackTrace();
		}
	}

}

