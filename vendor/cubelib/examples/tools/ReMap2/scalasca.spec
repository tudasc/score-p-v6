    <metrics>
      <metric>
        <disp_name>Time</disp_name>
        <uniq_name>time</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scalasca_patterns-2.0.html#time</url>
        <descr>Total CPU allocation time (includes time allocated for idle threads)</descr>
        <metric type="PREDERIVED_EXCLUSIVE">
          <disp_name>Execution</disp_name>
          <uniq_name>execution</uniq_name>
          <dtype>FLOAT</dtype>
          <uom>sec</uom>
          <url>@mirror@scalasca_patterns-2.0.html#execution</url>
          <descr>Execution time (does not include time allocated for idle threads)</descr>
          <cubepl>{ 
  		if (not(${calculation::region::description} eq "EPIK")) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	</cubepl>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>MPI</disp_name>
            <uniq_name>mpi</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi</url>
            <descr>Time spent in MPI calls</descr>
      	  <cubepl>{ 
  		    if (${calculation::region::description} eq "MPI") 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  	  </cubepl>
            <metric type="PREDERIVED_EXCLUSIVE">
              <disp_name>Synchronization</disp_name>
              <uniq_name>mpi_synchronization</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_synchronization</url>
              <descr>Time spent in MPI synchronization calls</descr>
  	    <cubepl>{if (
  		    (${calculation::region::description} eq "MPI") 
  		    and 
  		    (
  			(${calculation::region::name} seq "mpi_barrier" )
  			or 
  			(${calculation::region::name} seq "mpi_win_post" )
  			or 
  			(${calculation::region::name} seq "mpi_win_wait" )
  			or  
  			(${calculation::region::name} seq "mpi_win_start" )
  			or  
  			(${calculation::region::name} seq "mpi_win_complete" )
  			or  
  			(${calculation::region::name} seq "mpi_win_fence" )
  			or
  			(${calculation::region::name} seq "mpi_win_lock" )
  			or  
  			(${calculation::region::name} seq "mpi_win_unlock" )
  		    )
  		    ) {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} else {${a}=0;}; return ${a}; }
  	    </cubepl>
              <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Collective</disp_name>
                <uniq_name>mpi_sync_collective</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_sync_collective</url>
                <descr>Time spent in MPI barriers</descr>
  	      <cubepl>{
  			if ( 
  			    (${calculation::region::description} eq "MPI") 
  			    and 
  			    (
  				(${calculation::region::name} seq "mpi_barrier" )
  			    )
  			    ) 
  			    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  			else 
  			    {${a}=0;}; 
  			return ${a}; 
  			}
  	      </cubepl>
                <metric>
  		  <!-- this metric is going to be copied... as i understand-->
                  <disp_name>Wait at Barrier</disp_name>
                  <uniq_name>mpi_barrier_wait</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_barrier_wait</url>
                  <descr>Waiting time in front of MPI barriers</descr>
                </metric>
  	       <!-- this metric is going to be copied... as i understand-->
                <metric>
                  <disp_name>Barrier Completion</disp_name>
                  <uniq_name>mpi_barrier_completion</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_barrier_completion</url>
                  <descr>Time needed to finish an MPI barrier</descr>
                </metric>
              </metric>
              <metric type="PREDERIVED_EXCLUSIVE">
                <disp_name>Remote Memory Access</disp_name>
                <uniq_name>mpi_rma_synchronization</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_synchronization</url>
                <descr>Time spent in MPI RMA synchronization calls</descr>
  	       <cubepl>{
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(
  			    (${calculation::region::name} seq "mpi_win_post" )
  			    or 
  			    (${calculation::region::name} seq "mpi_win_wait" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_start" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_complete" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_fence" )
  			    or
  			    (${calculation::region::name} seq "mpi_win_lock" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_unlock" )
  			)
  			) 
  			    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  			else 
  			    {${a}=0;}; 
  			return ${a}; 
  		    }
  		</cubepl>
                <metric type="PREDERIVED_EXCLUSIVE">
                  <disp_name>Active Target</disp_name>
                  <uniq_name>mpi_rma_sync_active</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_sync_active</url>
                  <descr>Time spent in MPI RMA active target synchronization calls</descr>
  		<cubepl>{
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(		    
  			    (${calculation::region::name} seq "mpi_win_post" )
  			    or 
  			    (${calculation::region::name} seq "mpi_win_wait" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_start" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_complete" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_fence" )
  			  )
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  		 </cubepl>
                  <metric >
  		  <!-- this metric is going to be copied... as i understand-->		    
                    <disp_name>Late Post</disp_name>
                    <uniq_name>mpi_rma_late_post</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_late_post</url>
                    <descr>Waiting time in MPI RMA general active target synchronization due to a late post call</descr>
                  </metric>
                  <metric >
  		  <!-- this metric is going to be copied... as i understand-->			    
                    <disp_name>Wait at Fence</disp_name>
                    <uniq_name>mpi_rma_wait_at_fence</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_wait_at_fence</url>
                    <descr>Waiting time in MPI RMA due to inherent synchronization in MPI_Win_fence</descr>
                    <metric >
  		  <!-- this metric is going to be copied... as i understand-->			      
                      <disp_name>Early Fence</disp_name>
                      <uniq_name>mpi_rma_early_fence</uniq_name>
                      <dtype>FLOAT</dtype>
                      <uom>sec</uom>
                      <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_early_fence</url>
                      <descr>Waiting time in MPI RMA synchronization due to pending RMA ops</descr>
                    </metric>
                  </metric>
                  <metric >
  		  <!-- this metric is going to be copied... as i understand-->			    
                    <disp_name>Early Wait</disp_name>
                    <uniq_name>mpi_rma_early_wait</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_early_wait</url>
                    <descr>Waiting time in MPI RMA general active target synchronization due to an early wait call</descr>
                    <metric >
  		  <!-- this metric is going to be copied... as i understand-->			      
                      <disp_name>Late Complete</disp_name>
                      <uniq_name>mpi_rma_late_complete</uniq_name>
                      <dtype>FLOAT</dtype>
                      <uom>sec</uom>
                      <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_late_complete</url>
                      <descr>Waiting time in MPI RMA general active target synchronization due to unnecessary time between last RMA op and synchronization call</descr>
                    </metric>
                  </metric>
                </metric>
                <metric  type="PREDERIVED_EXCLUSIVE">
                  <disp_name>Passive Target</disp_name>
                  <uniq_name>mpi_rma_sync_passive</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_sync_passive</url>
                  <descr>Time spent in MPI RMA passive target synchronization calls</descr>
  	       <cubepl>{
  		   if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(
  			    (${calculation::region::name} seq "mpi_win_lock" )
  			    or  
  			    (${calculation::region::name} seq "mpi_win_unlock" )
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>
                </metric>
              </metric>
            </metric>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>Communication</disp_name>
              <uniq_name>mpi_communication</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_communication</url>
              <descr>Time spent in MPI communication calls</descr>
  	       <cubepl>{
  		   if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(		   
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*buffer/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*cancel/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*get_count/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*probe/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*recv/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*request/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_.*send/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_test/ )
  			    or 
  			    (lowercase(${calculation::region::name}) =~ /^mpi_wait/ )
  			    or 
  			    (
  				not(lowercase(${calculation::region::name}) =~ /^mpi_win/)
  				    and
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*start/)
  			    )	   
  			    
  			    or 
  			    
  			    (${calculation::region::name} seq "mpi_get" )
  			    or  
  			    (${calculation::region::name} seq "mpi_put" )
  			    or  
  			    (${calculation::region::name} seq "mpi_accumulate" )
  			    
  			    or 
  			    
  			    (${calculation::region::name} seq "mpi_allgather" )
  			    or  
  			    (${calculation::region::name} seq "mpi_allgatherv" )
  			    or  
  			    (${calculation::region::name} seq "mpi_allreduce" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoall" )
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoallv" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoallw" )
  			    or  
  			    (${calculation::region::name} seq "mpi_bcast" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_exscan" )
  			    or  
  			    (${calculation::region::name} seq "mpi_gather" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_gatherv" )
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce_scatter" )
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce_scatter_block" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_scan" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_scatter" )
  			    or  
  			    (${calculation::region::name} seq "mpi_scatterv" )			
  			 )   
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>	    
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Point-to-point</disp_name>
                <uniq_name>mpi_point2point</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_point2point</url>
                <descr>MPI point-to-point communication</descr>
  		<cubepl>{
  		   if ( 
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(
  			    ( lowercase(${calculation::region::name}) =~  /^mpi_/ )
  			    and 
  			    (
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*buffer/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*cancel/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*get_count/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*probe/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*recv/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*request/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_.*send/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_test/ )
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_wait/ )
  				or 
  				(
  				    not(lowercase(${calculation::region::name}) =~ /^mpi_win/)
  					and
  				    (lowercase(${calculation::region::name}) =~ /^mpi_.*start/)
  				)
  			    )
  			)
  			)
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  			    else 
  			{${a}=0;}; 
  			return ${a}; 
  			}
  		</cubepl>
                <metric >
  		  <!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Late Sender</disp_name>
                  <uniq_name>mpi_latesender</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_latesender</url>
                  <descr>Time a receiving process is waiting for a message</descr>
                  <metric >
  		  <!-- this metric is going to be copied... as i understand-->				    
                    <disp_name>Messages in Wrong Order</disp_name>
                    <uniq_name>mpi_latesender_wo</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#mpi_latesender_wo</url>
                    <descr>Late Sender situation due to messages received in the wrong order</descr>
                    <metric >
  		  <!-- this metric is going to be copied... as i understand-->				      
                      <disp_name>From different sources</disp_name>
                      <uniq_name>mpi_lswo_different</uniq_name>
                      <dtype>FLOAT</dtype>
                      <uom>sec</uom>
                      <url>@mirror@scalasca_patterns-2.0.html#mpi_lswo_different</url>
                      <descr>Wrong order situation due to messages received from different sources</descr>
                    </metric>
                    <metric >
  		  <!-- this metric is going to be copied... as i understand-->				      
                      <disp_name>From same source</disp_name>
                      <uniq_name>mpi_lswo_same</uniq_name>
                      <dtype>FLOAT</dtype>
                      <uom>sec</uom>
                      <url>@mirror@scalasca_patterns-2.0.html#mpi_lswo_same</url>
                      <descr>Wrong order situation due to messages received from the same source</descr>
                    </metric>
                  </metric>
                </metric>
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Late Receiver</disp_name>
                  <uniq_name>mpi_latereceiver</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_latereceiver</url>
                  <descr>Time a sending process is waiting for the receiver to become ready</descr>
                </metric>
              </metric>
              <metric   type="PREDERIVED_EXCLUSIVE">
                <disp_name>Collective</disp_name>
                <uniq_name>mpi_collective</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_collective</url>
                <descr>MPI collective communication</descr>
  	       <cubepl>{
  		   if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(
  			    (${calculation::region::name} seq "mpi_allgather" )
  			    or  
  			    (${calculation::region::name} seq "mpi_allgatherv" )
  			    or  
  			    (${calculation::region::name} seq "mpi_allreduce" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoall" )
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoallv" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_alltoallw" )
  			    or  
  			    (${calculation::region::name} seq "mpi_bcast" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_exscan" )
  			    or  
  			    (${calculation::region::name} seq "mpi_gather" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_gatherv" )
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce_scatter" )
  			    or  
  			    (${calculation::region::name} seq "mpi_reduce_scatter_block" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_scan" )			
  			    or  
  			    (${calculation::region::name} seq "mpi_scatter" )
  			    or  
  			    (${calculation::region::name} seq "mpi_scatterv" )			
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>	    
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Early Reduce</disp_name>
                  <uniq_name>mpi_earlyreduce</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_earlyreduce</url>
                  <descr>Waiting time due to an early receiver in MPI n-to-1 operations</descr>
                </metric>
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Early Scan</disp_name>
                  <uniq_name>mpi_earlyscan</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_earlyscan</url>
                  <descr>Waiting time due to an early receiver in an MPI scan operation</descr>
                </metric>
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Late Broadcast</disp_name>
                  <uniq_name>mpi_latebroadcast</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_latebroadcast</url>
                  <descr>Waiting time due to a late sender in MPI 1-to-n operations</descr>
                </metric>
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Wait at N x N</disp_name>
                  <uniq_name>mpi_wait_nxn</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_wait_nxn</url>
                  <descr>Waiting time due to inherent synchronization in MPI n-to-n operations</descr>
                </metric>
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>N x N Completion</disp_name>
                  <uniq_name>mpi_nxn_completion</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_nxn_completion</url>
                  <descr>Time needed to finish a N-to-N collective operation</descr>
                </metric>
              </metric>
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Remote Memory Access</disp_name>
                <uniq_name>mpi_rma_communication</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_communication</url>
                <descr>MPI remote memory access communication</descr>
  	       <cubepl>{
  		   if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(		   
  			    (${calculation::region::name} seq "mpi_get" )
  			    or  
  			    (${calculation::region::name} seq "mpi_put" )
  			    or  
  			    (${calculation::region::name} seq "mpi_accumulate" )
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>	      
                <metric >
  		<!-- this metric is going to be copied... as i understand-->				  
                  <disp_name>Early Transfer</disp_name>
                  <uniq_name>mpi_rma_early_transfer</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#mpi_rma_early_transfer</url>
                  <descr>Waiting time due to an early transfer to target location in MPI RMA operations</descr>
                </metric>
              </metric>
            </metric>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>File I/O</disp_name>
              <uniq_name>mpi_io</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_io</url>
              <descr>Time spent in MPI file I/O calls</descr>
  	    <cubepl>{
  		if (
  		    (${calculation::region::description} eq "MPI") 
  		    and 
  		    (		
  			lowercase(${calculation::region::name}) =~  /^mpi_file/ 
  		    )
  		    )
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		    }
  	    </cubepl>		    
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Collective</disp_name>
                <uniq_name>mpi_io_collective</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_io_collective</url>
                <descr>Time spent in collective MPI file I/O calls</descr>
  		<cubepl>{
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(			    
  			    (lowercase(${calculation::region::name}) =~  /^mpi_file/ )
  			    and 
  			    (
  			    not ( lowercase(${calculation::region::name}) =~  /^mpi_file_set_err/  )
  			    )
  			    and 
  			    (
  				(lowercase(${calculation::region::name}) seq "mpi_file_open")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_close")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_preallocate")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_seek_shared")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_sync")
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_all/)
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_ordered/)
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_set/)
  				
  			    )
  			)
  			)
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>		      
              </metric>
            </metric>
  	  <metric  type="PREDERIVED_EXCLUSIVE">
  	    <disp_name>Init/Exit</disp_name>
  	    <uniq_name>mpi_init_exit</uniq_name>
  	    <dtype>FLOAT</dtype>
  	    <uom>sec</uom>
  	    <url>@mirror@scalasca_patterns-2.0.html#mpi_init_exit</url>
  	    <descr>Time spent in MPI initialization calls</descr>
  	    <cubepl>{ 
  			if (
  			    (${calculation::region::description} eq "MPI") 
  			    and 
  			    (
  				(${calculation::region::name} seq "mpi_init")
  				or
  				(${calculation::region::name} seq "mpi_init_thread")
  				or 
  				(${calculation::region::name} seq "mpi_finalize")
  			    )
  			    ) 
  			    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  			else 
  			    {${a}=0;}; 
  			return ${a}; 
  			}
  	    </cubepl>
  	    </metric>
  	</metric>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>OMP</disp_name>
            <uniq_name>omp_time</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.0.html#omp_time</url>
            <descr>Time spent in the OpenMP run-time system and API</descr>
  	    <cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		     and 
  		    (
  		       (lowercase(${calculation::region::name}) =~ /^!\$omp flush/ )
  		       or 
  		       (lowercase(${calculation::region::name}) =~ /^!\$omp parallel/ )
  		       or
  		       (lowercase(${calculation::region::name}) =~ /^!\$omp barrier/ )
  			or 
  			(lowercase(${calculation::region::name}) =~ /^!\$omp implicit barrier/ )
  			or 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^omp_/ )
  			    and 
  			    (lowercase(${calculation::region::name}) =~ /_lock$/ )
  			)
  			or
  			(
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp atomic/ )
  				or 
  			    (
  				(lowercase(${calculation::region::name}) =~ /^!\$omp critical/ )
  				    and 
  				(lowercase(${calculation::region::name}) =~ /^!\$omp critical.*\ssblock/ )
  			    )
  			)
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>Flush</disp_name>
              <uniq_name>omp_flush</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#omp_flush</url>
              <descr>Time spent in the OpenMP flush directives</descr>
  	    <cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		    and 
  		    (
  			(lowercase(${calculation::region::name}) =~ /^!\$omp flush/ )
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>	    
            </metric>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>Management</disp_name>
              <uniq_name>omp_management</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#omp_management</url>
              <descr>Time needed to start up and shut down team of threads</descr>
  	    <cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		    and 
  		    (
  			(lowercase(${calculation::region::name}) =~ /^!\$omp parallel/ )
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>		    
              <metric >
                <disp_name>Fork</disp_name>
                <uniq_name>omp_fork</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#omp_fork</url>
                <descr>Time needed to create team of threads</descr>
              </metric>
            </metric>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>Synchronization</disp_name>
              <uniq_name>omp_synchronization</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#omp_synchronization</url>
              <descr>Time spent on OpenMP synchronization</descr>
  	    <cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		    and 
  		    (
  			(lowercase(${calculation::region::name}) =~ /^!\$omp barrier/ )
  			or 
  			(lowercase(${calculation::region::name}) =~ /^!\$omp ibarrier/ )
  			or 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^omp_/ )
  			    and 
  			    (lowercase(${calculation::region::name}) =~ /_lock$/ )
  			)
  			or
  			(
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp atomic/ )
  				or 
  			    (
  				(lowercase(${calculation::region::name}) =~ /^!\$omp critical/ )
  				    and 
  				(lowercase(${calculation::region::name}) =~ /^!\$omp critical.*\ssblock/ )
  			    )
  			)
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>	
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Barrier</disp_name>
                <uniq_name>omp_barrier</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#omp_barrier</url>
                <descr>OpenMP barrier synchronization</descr>
  		<cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		    and 
  		    (
  			(lowercase(${calculation::region::name}) =~ /^!\$omp barrier/ )
  			or 
  			(lowercase(${calculation::region::name}) =~ /^!\$omp ibarrier/ )
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>	
                <metric  type="PREDERIVED_EXCLUSIVE">
                  <disp_name>Explicit</disp_name>
                  <uniq_name>omp_ebarrier</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#omp_ebarrier</url>
                  <descr>Time spent in explicit OpenMP barriers</descr>
  		<cubepl>{ 
  		    if (
  			(${calculation::region::description} eq "OMP") 
  			and 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp barrier/ )
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  		</cubepl>	
                  <metric >
                    <disp_name>Wait at Barrier</disp_name>
                    <uniq_name>omp_ebarrier_wait</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#omp_ebarrier_wait</url>
                    <descr>Waiting time in front of explicit OpenMP barriers</descr>
                  </metric>
                </metric>
                <metric  type="PREDERIVED_EXCLUSIVE">
                  <disp_name>Implicit</disp_name>
                  <uniq_name>omp_ibarrier</uniq_name>
                  <dtype>FLOAT</dtype>
                  <uom>sec</uom>
                  <url>@mirror@scalasca_patterns-2.0.html#omp_ibarrier</url>
                  <descr>Time spent in implicit OpenMP barriers</descr>
  		<cubepl>{ 
  		    if (
  			(${calculation::region::description} eq "OMP") 
  			and 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp ibarrier/ )
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  		</cubepl>	
                  <metric >
                    <disp_name>Wait at Barrier</disp_name>
                    <uniq_name>omp_ibarrier_wait</uniq_name>
                    <dtype>FLOAT</dtype>
                    <uom>sec</uom>
                    <url>@mirror@scalasca_patterns-2.0.html#omp_ibarrier_wait</url>
                    <descr>Time spent in explicit OpenMP barriers</descr>
                  </metric>
                </metric>
              </metric>
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Critical</disp_name>
                <uniq_name>omp_critical</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#omp_critical</url>
                <descr>Time spent in front of a critical section</descr>
  		<cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "OMP") 
  		    and 
  		    (
  			
  			(lowercase(${calculation::region::name}) =~ /^!\$omp atomic/ )
  			    or 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp critical/ )
  				and 
  			    (lowercase(${calculation::region::name}) =~ /^!\$omp critical.*\ssblock/ )
  			)
  		    )
  		    ) 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	    </cubepl>		      
              </metric>
              <metric  type="PREDERIVED_EXCLUSIVE">
                <disp_name>Lock API</disp_name>
                <uniq_name>omp_lock_api</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#omp_lock_api</url>
                <descr>Time spent in OpenMP API calls dealing with locks</descr>
  		<cubepl>{ 
  		    if (
  			(${calculation::region::description} eq "OMP") 
  			and 
  			(
  			    (lowercase(${calculation::region::name}) =~ /^omp_/ )
  			    and 
  			    (lowercase(${calculation::region::name}) =~ /_lock$/ )
  			)
  			) 
  			{${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  		</cubepl>	
   	      
              </metric>
              <metric >
                <disp_name>Ordered</disp_name>
                <uniq_name>omp_ordered</uniq_name>
                <dtype>FLOAT</dtype>
                <uom>sec</uom>
                <url>@mirror@scalasca_patterns-2.0.html#omp_ordered</url>
                <descr>Time spent in front of an ordered region</descr>
              </metric>
            </metric>
          </metric>
          </metric>
        <metric type="PREDERIVED_EXCLUSIVE">
          <disp_name>Overhead</disp_name>
          <uniq_name>overhead</uniq_name>
          <dtype>FLOAT</dtype>
          <uom>sec</uom>
          <url>@mirror@scalasca_patterns-2.0.html#overhead</url>
          <descr>Time spent performing tasks related to trace generation</descr>
          <cubepl>
  	    { 
  		if (${calculation::region::description} eq "EPIK") 
  		    {${a}=metric::time(*,*)-metric::omp_idle_threads(*,*);} 
  		 else 
  		    {${a}=0;}; 
  		return ${a}; 
  	    }</cubepl>
        </metric>
        <metric >
          <disp_name>Idle threads</disp_name>
          <uniq_name>omp_idle_threads</uniq_name>
          <dtype>FLOAT</dtype>
          <uom>sec</uom>
          <url>@mirror@scalasca_patterns-2.0.html#omp_idle_threads</url>
          <descr>Unused CPU reservation time</descr>
          <metric >
            <disp_name>Limited parallelism</disp_name>
            <uniq_name>omp_limited_parallelism</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.0.html#omp_limited_parallelism</url>
            <descr>Unused CPU reservation time in parallel regions due to limited parallelism</descr>
          </metric>
        </metric>
      </metric>
      <metric >
        <disp_name>Visits</disp_name>
        <uniq_name>visits</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.0.html#visits</url>
        <descr>Number of visits</descr>
      </metric>
      <metric  type="POSTDERIVED">
        <disp_name>Synchronizations</disp_name>
        <uniq_name>syncs</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.0.html#syncs</url>
        <descr>Number of synchronization operations</descr>
        <cubepl> metric::syncs_p2p() + metric::syncs_coll()  + metric::syncs_rma() </cubepl>
        <metric  type="POSTDERIVED">
          <disp_name>Point-to-point</disp_name>
          <uniq_name>syncs_p2p</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#syncs_p2p</url>
          <descr>Number of point-to-point synchronization operations</descr>
  	<cubepl> metric::syncs_send() + metric::syncs_recv()  </cubepl>
          <metric >
            <disp_name>Sends</disp_name>
            <uniq_name>syncs_send</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#syncs_send</url>
            <descr>Number of point-to-point send synchronization operations</descr>
            <metric >
              <disp_name>Late Receivers</disp_name>
              <uniq_name>mpi_slr_count</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_slr_count</url>
              <descr>Number of Late Receiver instances in synchronizations</descr>
            </metric>
          </metric>
          <metric >
            <disp_name>Receives</disp_name>
            <uniq_name>syncs_recv</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#syncs_recv</url>
            <descr>Number of point-to-point receive synchronization operations</descr>
            <metric >
              <disp_name>Late Senders</disp_name>
              <uniq_name>mpi_sls_count</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_sls_count</url>
              <descr>Number of Late Sender instances in synchronizations</descr>
              <metric >
                <disp_name>Messages in Wrong Order</disp_name>
                <uniq_name>mpi_slswo_count</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_slswo_count</url>
                <descr>Number of Late Sender instances in synchronizations were messages are received in wrong order</descr>
              </metric>
            </metric>
          </metric>
        </metric>
        <metric >
          <disp_name>Collective</disp_name>
          <uniq_name>syncs_coll</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#syncs_coll</url>
          <descr>Number of collective synchronization operations</descr>
        </metric>
        <metric  type="POSTDERIVED">
          <disp_name>Remote Memory Access</disp_name>
          <uniq_name>syncs_rma</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#syncs_rma</url>
          <descr>Number of Remote Memory Access synchronizations</descr>
  	<cubepl> metric::syncs_fence() + metric::syncs_gats()  + metric::syncs_locks() </cubepl>
          <metric type="PREDERIVED_EXCLUSIVE">
            <disp_name>Fences</disp_name>
            <uniq_name>syncs_fence</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#syncs_fence</url>
            <descr>Number of fence synchronizations</descr>
  	  <cubepl>{ 
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(${calculation::region::name} seq "mpi_win_fence" )
  			) 
  			{${a}=metric::visits(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  	</cubepl>
          </metric>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>GATS Epochs</disp_name>
            <uniq_name>syncs_gats</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#syncs_gats</url>
            <descr>Number of GATS epochs</descr>
  	 <cubepl> metric::syncs_gats_access() + metric::syncs_gats_exposure()  </cubepl>
            <metric >
              <disp_name>Access Epochs</disp_name>
              <uniq_name>syncs_gats_access</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#syncs_gats_access</url>
              <descr>Number of access epochs</descr>
  	    <cubepl>{ 
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(${calculation::region::name} seq "mpi_win_start" )
  			 
  			) 
  			{${a}=metric::visits(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  	</cubepl>
            </metric>
            <metric  type="PREDERIVED_EXCLUSIVE">
              <disp_name>Exposure Epochs</disp_name>
              <uniq_name>syncs_gats_exposure</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#syncs_gats_exposure</url>
              <descr>Number of exposure epochs</descr>
  	    <cubepl>{ 
  		    if (
  				(${calculation::region::description} eq "MPI") 
  				and 
  				(${calculation::region::name} seq "mpi_win_post" )
  				
  			) 
  			{${a}=metric::visits(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  		    }
  	    </cubepl>
            </metric>
          </metric>
          <metric >
            <disp_name>Locks</disp_name>
            <uniq_name>syncs_locks</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#syncs_locks</url>
            <descr>Number of locks</descr>
          </metric>
        </metric>
      </metric>
      <metric >
        <disp_name>Pairwise synchronizations for RMA</disp_name>
        <uniq_name>mpi_rma_pairsync_count</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.0.html#pwsyncs</url>
        <descr>Number of pairwise synchronizations using MPI RMA</descr>
        <metric >
          <disp_name>Unneeded synchronizations</disp_name>
          <uniq_name>mpi_rma_pairsync_unneeded_count</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#pwsyncs_unneeded</url>
          <descr>Number of unneeded pairwise synchronizations using MPI RMA</descr>
        </metric>
      </metric>
      <metric  type="POSTDERIVED">
        <disp_name>Communications</disp_name>
        <uniq_name>comms</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.0.html#comms</url>
        <descr>Number of communication operations</descr>
        <cubepl> metric::comms_p2p() + metric::comms_coll()  + metric::comms_rma() </cubepl>
        <metric  type="POSTDERIVED">
          <disp_name>Point-to-point</disp_name>
          <uniq_name>comms_p2p</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#comms_p2p</url>
          <descr>Number of point-to-point communication operations</descr>
  	 <cubepl> metric::comms_send() + metric::comms_recv() </cubepl>
          <metric >
            <disp_name>Sends</disp_name>
            <uniq_name>comms_send</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_send</url>
            <descr>Number of point-to-point send communication operations</descr>
            <metric >
              <disp_name>Late Receivers</disp_name>
              <uniq_name>mpi_clr_count</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_clr_count</url>
              <descr>Number of Late Receiver instances in communications</descr>
            </metric>
          </metric>
          <metric >
            <disp_name>Receives</disp_name>
            <uniq_name>comms_recv</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_recv</url>
            <descr>Number of point-to-point receive communication operations</descr>
            <metric >
              <disp_name>Late Senders</disp_name>
              <uniq_name>mpi_cls_count</uniq_name>
              <dtype>INTEGER</dtype>
              <uom>occ</uom>
              <url>@mirror@scalasca_patterns-2.0.html#mpi_cls_count</url>
              <descr>Number of Late Sender instances in communications</descr>
              <metric >
                <disp_name>Messages in Wrong Order</disp_name>
                <uniq_name>mpi_clswo_count</uniq_name>
                <dtype>INTEGER</dtype>
                <uom>occ</uom>
                <url>@mirror@scalasca_patterns-2.0.html#mpi_clswo_count</url>
                <descr>Number of Late Sender instances in communications were messages are received in wrong order</descr>
              </metric>
            </metric>
          </metric>
        </metric>
        <metric  type="POSTDERIVED">
          <disp_name>Collective</disp_name>
          <uniq_name>comms_coll</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#comms_coll</url>
          <descr>Number of collective communication operations</descr>
  	 <cubepl> metric::comms_cxch() + metric::comms_csrc() + metric::comms_cdst()  </cubepl>
          <metric >
            <disp_name>Exchange</disp_name>
            <uniq_name>comms_cxch</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_cxch</url>
            <descr>Number of collective communications as source and destination</descr>
          </metric>
          <metric >
            <disp_name>As source</disp_name>
            <uniq_name>comms_csrc</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_csrc</url>
            <descr>Number of collective communications as source</descr>
          </metric>
          <metric >
            <disp_name>As destination</disp_name>
            <uniq_name>comms_cdst</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_cdst</url>
            <descr>Number of collective communications as destination</descr>
          </metric>
        </metric>
        <metric  type="POSTDERIVED">
          <disp_name>Remote Memory Access</disp_name>
          <uniq_name>comms_rma</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#comms_rma</url>
          <descr>Number of remote memory access operations</descr>
  	  <cubepl> metric::comms_rma_gets() + metric::comms_rma_puts() </cubepl>	
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Puts</disp_name>
            <uniq_name>comms_rma_puts</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_rma_puts</url>
            <descr>Number of RMA put and accumulate operations</descr>
  	  <cubepl>{ 
  	    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(		   
  			    (${calculation::region::name} seq "mpi_put" )
  			    or  
  			    (${calculation::region::name} seq "mpi_accumulate" )
  			)
  		) 
  		{${a}=metric::visits(*,*);} 
  	    else 
  		{${a}=0;}; 
  	    return ${a}; 
  	    }
  	</cubepl>
          </metric>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Gets</disp_name>
            <uniq_name>comms_rma_gets</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#comms_rma_gets</url>
            <descr>Number of RMA get operations</descr>
  	  <cubepl>{ 
  	    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(		   
  			    (${calculation::region::name} seq "mpi_get" )
  			)
  		) 
  		{${a}=metric::visits(*,*);} 
  	    else 
  		{${a}=0;}; 
  	    return ${a}; 
  	    }
  	</cubepl>	  
          </metric>
        </metric>
      </metric>
      <metric  type="POSTDERIVED">
        <disp_name>Bytes transferred</disp_name>
        <uniq_name>bytes</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>bytes</uom>
        <url>@mirror@scalasca_patterns-2.0.html#bytes</url>
        <descr>Number of bytes transferred</descr>
        <cubepl> metric::bytes_p2p() + metric::bytes_coll()  + metric::bytes_rma() </cubepl>
        <metric  type="POSTDERIVED">
          <disp_name>Point-to-point</disp_name>
          <uniq_name>bytes_p2p</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>bytes</uom>
          <url>@mirror@scalasca_patterns-2.0.html#bytes_p2p</url>
          <descr>Number of bytes transferred in point-to-point communication operations</descr>
  	<cubepl> metric::bytes_sent() + metric::bytes_rcvd()</cubepl>
          <metric >
            <disp_name>Sent</disp_name>
            <uniq_name>bytes_sent</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_sent</url>
            <descr>Number of bytes sent in point-to-point communication operations</descr>
          </metric>
          <metric >
            <disp_name>Received</disp_name>
            <uniq_name>bytes_rcvd</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_rcvd</url>
            <descr>Number of bytes received in point-to-point communication operations</descr>
          </metric>
        </metric>
        <metric  type="POSTDERIVED">
          <disp_name>Collective</disp_name>
          <uniq_name>bytes_coll</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>bytes</uom>
          <url>@mirror@scalasca_patterns-2.0.html#bytes_coll</url>
          <descr>Number of bytes transferred in collective communication operations</descr>
  	<cubepl> metric::bytes_cout() + metric::bytes_cin()</cubepl>
          <metric >
            <disp_name>Outgoing</disp_name>
            <uniq_name>bytes_cout</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_cout</url>
            <descr>Number of bytes outgoing in collective communication operations</descr>
          </metric>
          <metric >
            <disp_name>Incoming</disp_name>
            <uniq_name>bytes_cin</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_cin</url>
            <descr>Number of bytes incoming in collective communication operations</descr>
          </metric>
        </metric>
        <metric  type="POSTDERIVED">
          <disp_name>Remote Memory Access</disp_name>
          <uniq_name>bytes_rma</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>bytes</uom>
          <url>@mirror@scalasca_patterns-2.0.html#bytes_rma</url>
          <descr>Number of bytes transferred in remote memory access operations</descr>
  	<cubepl> metric::bytes_put() + metric::bytes_get()</cubepl>
          <metric >
            <disp_name>Sent</disp_name>
            <uniq_name>bytes_put</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_put</url>
            <descr>Number of bytes sent in remote memory access operations</descr>
          </metric>
          <metric >
            <disp_name>Received</disp_name>
            <uniq_name>bytes_get</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#bytes_get</url>
            <descr>Number of bytes received in remote memory access operations</descr>
          </metric>
        </metric>
      </metric>
      
      <metric  type="PREDERIVED_EXCLUSIVE">
        <disp_name>MPI file operations</disp_name>
        <uniq_name>mpi_file_ops</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>occ</uom>
        <url>@mirror@scalasca_patterns-2.0.html#mpi_file_ops</url>
        <descr>Number of MPI file operations</descr>
  	<cubepl>{ 
  	if (
  		    (${calculation::region::description} eq "MPI") 
  		    and 
  		    (		   
  			(${calculation::region::name} seq "mpi_file" )
  		    )
  	    ) 
  	    {${a}=metric::visits(*,*);} 
  	else 
  	    {${a}=0;}; 
  	return ${a}; 
  	}
      </cubepl>      
        <metric  type="PREDERIVED_EXCLUSIVE">
          <disp_name>Individual</disp_name>
          <uniq_name>mpi_file_iops</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#mpi_file_iops</url>
          <descr>Number of individual MPI file operations</descr>
  		<cubepl>{
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(lowercase(${calculation::region::name}) =~  /^mpi_file/ )
  			and 
  			 not (
  				(
  				not ( lowercase(${calculation::region::name}) =~  /^mpi_file_set_err/  )
  				)
  				and 
  				(
  				    (lowercase(${calculation::region::name}) seq "mpi_file_open")
  				    or 
  				    (lowercase(${calculation::region::name}) seq "mpi_file_close")
  				    or 
  				    (lowercase(${calculation::region::name}) seq "mpi_file_preallocate")
  				    or 
  				    (lowercase(${calculation::region::name}) seq "mpi_file_seek_shared")
  				    or 
  				    (lowercase(${calculation::region::name}) seq "mpi_file_sync")
  				    or 
  				    (lowercase(${calculation::region::name}) =~ /^mpi_file.*_all/)
  				    or 
  				    (lowercase(${calculation::region::name}) =~ /^mpi_file.*_ordered/)
  				    or 
  				    (lowercase(${calculation::region::name}) =~ /^mpi_file.*_set/)
  				    
  				)
  			)
  			)
  			{${a}=metric::visits(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>		      

          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Reads</disp_name>
            <uniq_name>mpi_file_irops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_irops</url>
            <descr>Number of individual MPI file read operations</descr>
  	 <cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "MPI") 
  		    and 
  		    (${calculation::region::name} seq "mpi_file" )
  		    and 
  		    (${calculation::region::name} =~ /read/ )
  		    ) 
  		    {${a}=metric::visits(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	</cubepl> 
          </metric>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Writes</disp_name>
            <uniq_name>mpi_file_iwops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_iwops</url>
            <descr>Number of individual MPI file write operations</descr>
  	    <cubepl>{ 
  	    if (
  		(${calculation::region::description} eq "MPI") 
  		and 
  		(${calculation::region::name} seq "mpi_file" )
  		and 
  		(${calculation::region::name} =~ /write/ )
  		) 
  		{${a}=metric::visits(*,*);} 
  	    else 
  		{${a}=0;}; 
  	    return ${a}; 
  	    }
  	</cubepl> 
          </metric>
        </metric>
        <metric  type="PREDERIVED_EXCLUSIVE">
          <disp_name>Collective</disp_name>
          <uniq_name>mpi_file_cops</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>occ</uom>
          <url>@mirror@scalasca_patterns-2.0.html#mpi_file_cops</url>
          <descr>Number of collective MPI file operations</descr>
  	<cubepl>{
  		    if (
  			(${calculation::region::description} eq "MPI") 
  			and 
  			(			    
  			    (lowercase(${calculation::region::name}) =~  /^mpi_file/ )
  			    and 
  			    (
  			    not ( lowercase(${calculation::region::name}) =~  /^mpi_file_set_err/  )
  			    )
  			    and 
  			    (
  				(lowercase(${calculation::region::name}) seq "mpi_file_open")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_close")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_preallocate")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_seek_shared")
  				or 
  				(lowercase(${calculation::region::name}) seq "mpi_file_sync")
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_all/)
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_ordered/)
  				or 
  				(lowercase(${calculation::region::name}) =~ /^mpi_file.*_set/)
  				
  			    )
  			)
  			)
  			{${a}=metric::visits(*,*);} 
  		    else 
  			{${a}=0;}; 
  		    return ${a}; 
  			}
  		</cubepl>		      

          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Reads</disp_name>
            <uniq_name>mpi_file_crops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_crops</url>
            <descr>Number of collective MPI file read operations</descr>
  	<cubepl>{ 
  		if (
  		    (${calculation::region::description} eq "MPI") 
  		    and 
  		    (${calculation::region::name} seq "mpi_file" )
  		    and 
  		    (${calculation::region::name} =~ /read/ )
  		    ) 
  		    {${a}=metric::visits(*,*);} 
  		else 
  		    {${a}=0;}; 
  		return ${a}; 
  		}
  	</cubepl> 
          </metric>
          <metric  type="PREDERIVED_EXCLUSIVE">
            <disp_name>Writes</disp_name>
            <uniq_name>mpi_file_cwops</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>occ</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_cwops</url>
            <descr>Number of collective MPI file write operations</descr>
  	    <cubepl>{ 
  	    if (
  		(${calculation::region::description} eq "MPI") 
  		and 
  		(${calculation::region::name} seq "mpi_file" )
  		and 
  		(${calculation::region::name} =~ /write/ )
  		) 
  		{${a}=metric::visits(*,*);} 
  	    else 
  		{${a}=0;}; 
  	    return ${a}; 
  	    }
  	</cubepl> 	  
          </metric>
        </metric>
      </metric>
      <metric >
        <disp_name>MPI file bytes transferred</disp_name>
        <uniq_name>mpi_file_bytes</uniq_name>
        <dtype>INTEGER</dtype>
        <uom>bytes</uom>
        <url>@mirror@scalasca_patterns-2.0.html#mpi_file_bytes</url>
        <descr>Number of bytes transferred in MPI file operations</descr>
        <metric >
          <disp_name>Individual</disp_name>
          <uniq_name>mpi_file_ibytes</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>bytes</uom>
          <url>@mirror@scalasca_patterns-2.0.html#mpi_file_ibytes</url>
          <descr>Number of bytes transferred in individual MPI file operations</descr>
          <metric >
            <disp_name>Read</disp_name>
            <uniq_name>mpi_file_irbytes</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_irbytes</url>
            <descr>Number of bytes read in individual MPI file operations</descr>
          </metric>
          <metric >
            <disp_name>Written</disp_name>
            <uniq_name>mpi_file_iwbytes</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_iwbytes</url>
            <descr>Number of bytes written in individual MPI file operations</descr>
          </metric>
        </metric>
        <metric >
          <disp_name>Collective</disp_name>
          <uniq_name>mpi_file_cbytes</uniq_name>
          <dtype>INTEGER</dtype>
          <uom>bytes</uom>
          <url>@mirror@scalasca_patterns-2.0.html#mpi_file_cbytes</url>
          <descr>Number of bytes transferred in collective MPI file operations</descr>
          <metric >
            <disp_name>Read</disp_name>
            <uniq_name>mpi_file_crbytes</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_crbytes</url>
            <descr>Number of bytes read in collective MPI file operations</descr>
          </metric>
          <metric >
            <disp_name>Written</disp_name>
            <uniq_name>mpi_file_cwbytes</uniq_name>
            <dtype>INTEGER</dtype>
            <uom>bytes</uom>
            <url>@mirror@scalasca_patterns-2.0.html#mpi_file_cwbytes</url>
            <descr>Number of bytes written in collective MPI file operations</descr>
          </metric>
        </metric>
      </metric>
        <metric>
        <disp_name>Computational imbalance</disp_name>
        <uniq_name>imbalance</uniq_name>
        <dtype>FLOAT</dtype>
        <uom>sec</uom>
        <url>@mirror@scalasca_patterns-2.0.html#imbalance</url>
        <descr>Computational load imbalance heuristic (see Online Description for details)</descr>
          <metric>
          <disp_name>Overload</disp_name>
          <uniq_name>imbalance_above</uniq_name>
          <dtype>FLOAT</dtype>
          <uom>sec</uom>
          <url>@mirror@scalasca_patterns-2.0.html#imbalance_above</url>
          <descr>Computational load imbalance heuristic (overload)</descr>
          <metric>
            <disp_name>Single participant</disp_name>
            <uniq_name>imbalance_above_single</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.0.html#imbalance_above_single</url>
            <descr>Computational load imbalance heuristic (single participant)</descr>
          </metric>
        </metric>
        <metric>
          <disp_name>Underload</disp_name>
          <uniq_name>imbalance_below</uniq_name>
          <dtype>FLOAT</dtype>
          <uom>sec</uom>
          <url>@mirror@scalasca_patterns-2.0.html#imbalance_below</url>
          <descr>Computational load imbalance heuristic (underload)</descr>
          <metric>
            <disp_name>Non-participation</disp_name>
            <uniq_name>imbalance_below_bypass</uniq_name>
            <dtype>FLOAT</dtype>
            <uom>sec</uom>
            <url>@mirror@scalasca_patterns-2.0.html#imbalance_below_bypass</url>
            <descr>Computational load imbalance heuristic (non-participation)</descr>
            <metric>
              <disp_name>Singularity</disp_name>
              <uniq_name>imbalance_below_singularity</uniq_name>
              <dtype>FLOAT</dtype>
              <uom>sec</uom>
              <url>@mirror@scalasca_patterns-2.0.html#imbalance_below_singularity</url>
              <descr>Computational load imbalance heuristic (non-participation in singularity)</descr>
            </metric>
          </metric>
        </metric>
      </metric>
    </metrics>
