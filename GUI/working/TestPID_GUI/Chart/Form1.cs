using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.IO.Ports;
using ZedGraph;


namespace Chart
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        int intlen;
        bool StateDraw = false;
        double TickStart;
        
        UInt32 i=0;
        //PointPairList listpoint = new PointPairList();
        //LineItem mycurve;

        private void btConnect_Click(object sender, EventArgs e)
        {
            if (cbbCom.Text == "")
            {
                MessageBox.Show("Select Com gate,please!", "Warning", MessageBoxButtons.OK);
            }
            else
            {
                btDisconnect.Enabled = true;
                btConnect.Enabled = false;
                gbRxData.Enabled = true;
                Com.PortName = cbbCom.Text;
                Com.Open();
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            btDisconnect.Enabled = false;
            gbRxData.Enabled = false;
            timer1.Enabled = true;
            btPause.Enabled = false;
            

            GraphPane MyPane = Graph.GraphPane;
            MyPane.Title.Text = "Display Graphic of DAC";
            MyPane.XAxis.Title.Text = "Time(s)";
            MyPane.YAxis.Title.Text = "Value(V)";

            RollingPointPairList list = new RollingPointPairList(60000);

            LineItem curve = MyPane.AddCurve("Voltage", list, Color.Blue, SymbolType.None);

            MyPane.XAxis.Scale.Max = 30;
            MyPane.XAxis.Scale.Min = 0;
            MyPane.XAxis.Scale.MinorStep = 1;
            MyPane.XAxis.Scale.MajorStep = 5;

            Graph.AxisChange();

            TickStart = Environment.TickCount;
        }
        private void Draw(double x, double y)
        {
            LineItem curve = Graph.GraphPane.CurveList[0] as LineItem;
            if (curve == null)
                return;

            IPointListEdit list = curve.Points as IPointListEdit;
            if (list == null)
                return;

            //double time = (Environment.TickCount - TickStart) / 1000;

            i++;
            list.Add(x,y);
            curve = Graph.GraphPane.AddCurve(null, list, Color.Blue, SymbolType.None);

            Scale xScale = Graph.GraphPane.XAxis.Scale;

            if (x > (xScale.Max - xScale.MajorStep))
            {
                xScale.Max = xScale.Max + xScale.MinorStep;
                xScale.Min = xScale.Max - 30;
            }

            Graph.AxisChange();
            Graph.Invalidate();
        }

        private void btDisconnect_Click(object sender, EventArgs e)
        {
            btConnect.Enabled = true;
            btDisconnect.Enabled = false;
            Com.Close();
            gbRxData.Enabled = false;
        }

        private void timer1_Tick(object sender, EventArgs e)
        {  
            string[] port = SerialPort.GetPortNames();
            if (intlen != port.Length)
            {
                intlen = port.Length;
                cbbCom.Items.Clear();
                cbbCom.Items.AddRange(port);
            }

            if (btPause.Enabled == true)
            {


                double time = (Environment.TickCount - TickStart) / 1000;

                double y = 3.3 * Math.Sin(time);

                Draw(time, y);
                txtData.Text = y.ToString();
            }
      
        }

        private void btStart_Click(object sender, EventArgs e)
        {
            StateDraw = true;
            btPause.Enabled = true;
            btStart.Enabled = false;
        }

        private void btPause_Click(object sender, EventArgs e)
        {
            StateDraw = false;
            btStart.Enabled = true;
            btPause.Enabled = false;
        }

        private void Graph_Load(object sender, EventArgs e)
        {

        }
    }
}
