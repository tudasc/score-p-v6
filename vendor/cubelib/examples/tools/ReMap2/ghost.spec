<metrics>
    <metric viztype="GHOST">
        <!-- This metric is copied from the trace analysis -->
        <disp_name>Time</disp_name>
        <uniq_name>time</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scalasca_patterns-2.1.html#time</url>
        <descr>Total CPU allocation time (includes time allocated for idle threads)</descr>
    </metric>
    <metric type="PREDERIVED_EXCLUSIVE">
	<disp_name>Experimenal metric 1</disp_name>
	<uniq_name>exp1</uniq_name>
	<dtype>FLOAT</dtype>
	<uom>sec</uom>
	<url>http://www.cs.utk.edu/sys.html</url>
	<descr>Experimental metric 1 with some issues </descr>
	<cubepl>
	{   
	    ${a}=0;   
	    if (${cube::region::name}[${calculation::region::id}] =~ /^MPI_/)    
	    {        
		${a}=metric::time();     
	    };  
	    return ${a};   
	} 
	</cubepl>
    </metric>
    <metric type="PREDERIVED_EXCLUSIVE">
	    <disp_name>Experimenal metric 2</disp_name>
	    <uniq_name>exp2</uniq_name>
	    <dtype>FLOAT</dtype>
	    <uom>sec</uom>
	    <url>http://www.cs.utk.edu/sys.html</url>
	    <descr>Completely wrong metric</descr>
	    <cubepl>
	    {   
		${a}=0;   
		if (not(${cube::region::name}[${calculation::region::id}] =~ /^MPI_/))   
		{        
		    ${a}=metric::time();     
		};  
		return ${a};   
	    } 
	</cubepl>
    </metric>
</metrics>
