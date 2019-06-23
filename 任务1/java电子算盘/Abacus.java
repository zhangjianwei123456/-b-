package 电子算盘;

import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JPanel;

public class Abacus extends JFrame
{

	/**
	 * 
	 */
	private static final long serialVersionUID = 7038003206059641665L;

	public int totalNumber;
	public int t = 0;
	public boolean[] isToUpper = new boolean[5];
	public int beadNumber[] = new int[5];

	protected int screenWidth = (int) this.getToolkit().getScreenSize().getWidth();
	protected int screenHeigth = (int) this.getToolkit().getScreenSize().getHeight();
	protected int width = 700;
	protected int height = 700;
	protected int x = (this.screenWidth - width) / 2;
	protected int y = (this.screenHeigth - height) / 2;

	protected String path_images = "src/images/";
	protected ImageIcon bead_1 = new ImageIcon(path_images + "qizi1.png");
	protected ImageIcon bead_2 = new ImageIcon(path_images + "qizi2.png");

	protected JFrame final_Frame = new JFrame();
	protected JPanel final_Bead_Panel = new JPanel(); //存放算盘的总标签
	protected JPanel up_Bead = new JPanel(); //存放上盘
	protected JPanel down_Bead = new JPanel(); //存放下盘
	protected Real_Clock clockk;  //时间类
	protected JButton buttons_up[][] = new JButton[2][5];
	protected JButton buttons_down[][] = new JButton[5][5];

	GridLayout gl_1 = new GridLayout(2, 5);
	GridLayout gl_2 = new GridLayout(5, 5);

	public Abacus()
	{
		frame();
		abacuspanel();
		clockk = new Real_Clock();
		clock();
	}

	public void frame()
	{
		final_Frame.setTitle("电子算盘");
		final_Frame.setVisible(true);
		final_Frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		final_Frame.setLocation(x, y);
		final_Frame.setSize(width, height);
		final_Frame.setLayout(null);
		final_Frame.setResizable(true);
	}

	public void abacuspanel()
	{
		final_Bead_Panel.setBounds(10, 60, 420, 590);
		final_Bead_Panel.setBackground(Color.BLACK);
		final_Bead_Panel.setLayout(null);
		final_Frame.add(final_Bead_Panel);
		up_Bead.setLayout(gl_1);
		up_Bead.setBounds(10, 10, 400, 160);
		up_Bead.setBackground(Color.WHITE);
		final_Bead_Panel.add(up_Bead);
		down_Bead.setLayout(gl_2);
		down_Bead.setBounds(10, 180, 400, 400);
		down_Bead.setBackground(Color.WHITE);
		final_Bead_Panel.add(down_Bead);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				buttons_up[i][j] = new JButton("");
				buttons_up[i][j].addActionListener(new ClickIt());
				buttons_up[i][j].setBorderPainted(false);
				buttons_up[i][j].setContentAreaFilled(false);
				if (i != 1)
				{
					buttons_up[i][j].setIcon(bead_1);
					buttons_up[i][j].setBackground(Color.GRAY);
				}
				up_Bead.add(buttons_up[i][j]);
			}
		}
		for (int i = 0; i < 5; i++)
		{
			for (int j = 0; j < 5; j++)
			{
				buttons_down[i][j] = new JButton("");
				buttons_down[i][j].addActionListener(new ClickIt());
				buttons_down[i][j].setBorderPainted(false);
				buttons_down[i][j].setContentAreaFilled(false);
				if (i != 0)
				{
					buttons_down[i][j].setIcon(bead_2);
					buttons_down[i][j].setBackground(Color.GRAY);
				}
				down_Bead.add(buttons_down[i][j]);
			}
		}
	}

	private void addTotalNumber()
	{
		for (int j = 0; j < 5; j++)
		{
			if (isToUpper[j] == true && beadNumber[j] < 5)
			{beadNumber[j] = beadNumber[j] + 5;}	
			else if (isToUpper[j] == false && beadNumber[j] >= 5)
			{beadNumber[j] = beadNumber[j] - 5;}
		}
		totalNumber = 0;
		for (int j = 0; j < 5; j++)
		{totalNumber = totalNumber + beadNumber[j] * (int) Math.pow(10, (double) j);}
		System.out.println(totalNumber);
	}

	class ClickIt implements ActionListener
	{
		public void actionPerformed(ActionEvent e)
		{
			for (int i = 0; i < 2; i++)
				for (int j = 0; j < 5; j++)
					if (e.getSource() == buttons_up[i][j])
					{
						if (i == 1)
						{
							isToUpper[5 - j - 1] = false;
							buttons_up[0][j].setIcon(bead_1);
							buttons_up[1][j].setIcon(null);
						} else if (i == 0)
						{
							isToUpper[5 - j - 1] = true;
							buttons_up[1][j].setIcon(bead_1);
							buttons_up[0][j].setIcon(null);
						}
					}
			for (int i = 0; i <= 4; i++)
				for (int j = 0; j < 5; j++)
					if (e.getSource() == buttons_down[i][j])
					{
						beadNumber[5 - j - 1] = i;
						for (int k = 1; k <= 4; k++)
						{buttons_down[k][j].setIcon(bead_2);}
						buttons_down[0][j].setIcon(bead_2);
						buttons_down[i][j].setIcon(null);
					}
			addTotalNumber();
		}
	}

	public void clock()
	{
		clockk.setBounds(490, 360, 140, 140);
		final_Frame.add(clockk);
	}
	
	public static void main(String[] args)
	{
		@SuppressWarnings("unused")
		Abacus a = new Abacus();
	}

}
